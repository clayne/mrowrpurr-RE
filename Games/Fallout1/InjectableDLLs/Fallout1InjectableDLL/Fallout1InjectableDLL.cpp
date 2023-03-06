#include <Hook.h>
#include <Injected_DLL.h>
#include <Logging.h>
#include <UserInterface.h>
#include <string_format.h>

#define Output(...) UserInterface::App().AppendOutput(string_format(__VA_ARGS__))

void DropItem_Detour() {
    auto& reg = Registers::Current();
    Output(
        "[FUNCTION] Drop Item: eax: {}, ebx: {}, ecx: {}, edx: {}, esi: {}, edi: {}, "
        "ebp: {}, esp: {}",
        reg.eax(), reg.ebx(), reg.ecx(), reg.edx(), reg.esi(), reg.edi(), reg.ebp(), reg.esp()
    );
}

void SetupHooks() {
    // Make a nice alias!
    // Add AOB (with option mask support)

    RegisterHook(0x46a41c, DropItem_Detour);
}

void RunUI() {
    UserInterface::Run([&](auto& app) {
        app.SetTitle("Fallout 1")
            .SetButtonHeight(50)
            .SetHeight(500)
            .SetWidth(500)
            .ShowOutputTextBox();
        for (auto& [name, hook] : GetRegisteredHooks()) {
            app.AddButton(string_format("Enable: {}", name), [&]() {
                if (hook->Toggle())
                    app.ChangeButtonText(string_format("Disable: {}", name));
                else
                    app.ChangeButtonText(string_format("Enable: {}", name));
            });
        }
        app.AddButton("Clear", [&]() { app.ClearOutput(); });
        app.AddButton("Eject DLL", [&]() { app.Close(); });
    });
}

DLL_Main {
    SetupHooks();
    RunUI();
    Injected_DLL::EjectDLL();
}
