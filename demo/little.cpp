#pragma once

#include <iostream>
#include <thread>
#include <chrono>

#include "soloud.h"
#include "soloud_wav.h"

int main(int argc, const char* argv[]) {
	/*
	const auto one_sixtieth_of_a_second = std::chrono::duration<double>(1. / 60.);
	const auto t1 = std::chrono::steady_clock::now();
	*/

	SoLoud::Soloud gSoloud;
	SoLoud::Wav gWave;

	gSoloud.init();

	gWave.load("assets/sounds/cheer.wav");

	double t = gWave.getLength();

	gSoloud.play(gWave);

	std::this_thread::sleep_for(std::chrono::duration<double>(t));
	/*
	const auto t2 = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_time = t2 - t1;
	std::chrono::duration<double> wait_time = one_sixtieth_of_a_second - elapsed_time;
	std::this_thread::sleep_for(wait_time);
	*/
	gSoloud.deinit();
}