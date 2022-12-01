-- SOURCE: https://github.com/xmake-io/xmake-repo/blob/master/packages/e/enet/xmake.lua

package("enet")

    set_homepage("http://enet.bespin.org")
    set_description("Reliable UDP networking library.")
    set_license("MIT")

    add_urls("https://github.com/lsalzman/enet/archive/refs/tags/$(version).tar.gz",
             "https://github.com/lsalzman/enet.git")

    add_versions("v1.3.17", "1e0b4bc0b7127a2d779dd7928f0b31830f5b3dcb7ec9588c5de70033e8d2434a")
    add_patches("v1.3.17", path.join(os.scriptdir(), "patches", "cmake.patch"), "e77d2d129952443d67c1ec432de81843d72b854d25bbd6fb244b0f85804d21d1")

    if is_plat("mingw") and is_subhost("msys") then
        add_extsources("pacman::enet")
    elseif is_plat("linux") then
        add_extsources("pacman::enet", "apt::libenet-dev")
    elseif is_plat("macosx") then
        add_extsources("brew::enet")
    end

    add_deps("cmake")

    if is_plat("windows", "mingw") then
        add_syslinks("winmm", "ws2_32")
    end

    on_load("windows", "mingw", function (package)
        if package:config("shared") then
            package:add("defines", "ENET_DLL")
        end
    end)

    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs)
   end)

    on_test(function (package)
        assert(package:check_cxxsnippets({test = [[
            void test()
            {
                if (enet_initialize () != 0)
                    return;

                ENetAddress address;
                ENetHost* server;
                address.host = ENET_HOST_ANY;
                address.port = 1234;
                server = enet_host_create (&address, 32, 2, 0, 0);
                if (server == NULL)
                    return;

                ENetEvent event;
                while (enet_host_service (server, &event, 1000) > 0);

                enet_host_destroy(server);
                enet_deinitialize();
            }
        ]]}, {includes = {"enet/enet.h"}}))
    end)