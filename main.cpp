#include "ObjectFile.hpp"
#include "args.hpp"
#include "machinetype.hpp"
string version = string(VERSION) + "-" + COMMIT_ID;
int main(int argc, char* argv[]) {
    if(argc<2) {
        assert(0&&"params number error");
    }    
    Context ctx = Context();
    vector<string> remaining = parseArgs(argc, argv, ctx);
    if (ctx.Args.Emulation==MachineType::None) {
        for(auto filename: remaining) {
            if (filename.substr(0,1)=="-")
                continue;
            ObjectFile file(filename);
            ctx.Args.Emulation = GetMachineTypeFormContents(file.contents);
            if (ctx.Args.Emulation !=MachineType::None)
                break;
        }
    }
    assert(ctx.Args.Emulation == MachineType::RISCV64 && "unknown emulation type");
    for(auto x: remaining) {
        cout << x << endl;
    }
    return 0;
}
  