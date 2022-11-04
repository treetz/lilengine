#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>

#include "spdlog/spdlog.h"

#include "Types.h"

namespace lilengine {

	// A unique 32 bit ID given to each game object.
	typedef uint32_t EntityID;

	// The Entity Component System takes care of creating, storing, 
	// accessing destroying, and itterating over game objects and their 
	// various components. 
	class ECS {
	public:
		// Returns the entity id of the created game object
		EntityID Create() {
			return ++current_ID;
		}

		// Destroy the entity by removing all components.
		void Destroy(EntityID entity) {
			for (const auto& comps : m_components) { comps->Drop(entity); }
		}

		// Allows access to a component of type T for the inputted entity.
		template< typename T >
		T& Get(EntityID entity) {
			return GetAppropriateSparseSet<T>()[entity];
		}

		typedef std::function<void(EntityID)> ForEachCallback;
		template<typename EntitiesThatHaveThisComponent, typename... AndAlsoTheseComponents>
		void ForEach(const ForEachCallback& callback) {
			// Iterate over elements of the first container.
			auto& container = GetAppropriateSparseSet<EntitiesThatHaveThisComponent>();
			for (const auto&[entity, value] : container) {
				// We know it has the first component.
				// Skip the entity if it doesn't have the remaining components.
				// This `if constexpr` is evaluated at compile time. It is needed when AndAlsoTheseComponents is empty.
				// https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
				if constexpr (sizeof...(AndAlsoTheseComponents) > 0) {
					if (!HasAll<AndAlsoTheseComponents...>(entity)) {
						continue;
					}
				}
				callback(entity);
			}
		}

	private:
		// Holds an unordered map of a component type T mapped to EntityIDs.
		class SparseSetHolder {
		public:
			// A virtual destructor, since we store pointers to this superclass yet have subclasses with destructors that need to run.
			virtual ~SparseSetHolder() = default;
			virtual bool Has(EntityID) const = 0;
			virtual void Drop(EntityID) = 0;
		};
		// Subclasses are templated on the component type they hold.
		template< typename T > class SparseSet : public SparseSetHolder {
		public:
			std::unordered_map< EntityID, T > data;
			bool Has(EntityID e) const override { return data.count(e) > 0; };
			void Drop(EntityID e) override { data.erase(e); };
		};

		// These functions are used to determine the index of the 
		// SparseSetHolder element within m_components that contains the 
		// component we want.
		typedef int ComponentIndex;
		template<typename T> ComponentIndex GetComponentIndex() {
			static ComponentIndex index = GetNextIndex(); // Only calls GetNextIndex() the first time this function is called.
			return index;
		}
		ComponentIndex GetNextIndex() {
			static ComponentIndex index = -1; // Returns the sequence 0, 1, 2, … every time this is called.
			index += 1;
			return index;
		}

		// Gets the unordered_map containing the component T.
		template< typename T >
		std::unordered_map< EntityID, T >& GetAppropriateSparseSet() {
			// Get the index for T’s SparseSet
			const ComponentIndex index = GetComponentIndex<T>();
			// If we haven’t seen it yet, it must be past the end.
			// Since component indices are shared by all ECS instances,
			// it could happen that index is more than one past the end.
			if (index >= m_components.size()) { m_components.resize(index + 1); }
			assert(index < m_components.size());
			// Create the actual sparse set if needed.
			if (m_components[index] == nullptr) m_components[index] = std::make_unique< SparseSet<T> >();
			// It’s safe to cast the SparseSetHolder to its subclass and return the std::unordered_map< EntityID, T > inside.
			return static_cast<SparseSet<T>&>(*m_components[index]).data;
		}

		// Returns true if the entity has all types.
		template <typename T, typename... Rest>
		bool HasAll(EntityID entity) {
			bool result = true;
			// https://stackoverflow.com/questions/48405482/variadic-template-no-matching-function-for-call/48405556#48405556
			if constexpr (sizeof...(Rest) > 0) { result = HasAll<Rest...>(entity); }
			return result && GetAppropriateSparseSet<T>().count(entity) > 0;
		}

		// m_components stores SparseSetHolders for every component in use
		std::vector< std::unique_ptr< SparseSetHolder > > m_components;

		EntityID current_ID = 0;
	};
}