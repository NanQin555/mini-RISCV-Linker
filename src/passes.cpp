#include "passes.hpp"
#include "context.hpp"

void passes::ResolveSymbols(Context* ctx) {
    for(auto file: ctx->Objs) {
        file->ResolveSymbols();
    }

    MarkLiveObjects(ctx);
    
    for(auto file: ctx->Objs) {
        if(!file->IsAlive) {
            file->ClearSymbols();
        }
    }

    ctx->Objs = RemoveIf<ObjectFile*>(ctx->Objs, [](ObjectFile* file) {
        return !file->IsAlive;
    });
}



void passes::MarkLiveObjects(Context* ctx) {
    vector<ObjectFile*> roots;
    for(auto file: ctx->Objs) {
        if(file->IsAlive) {
            roots.push_back(file);
        }
    }
    assert(roots.size() > 0);

    while(roots.size() > 0) {
        ObjectFile* file = roots.front();
        if (!file->IsAlive) 
            continue;
        file->MarkLiveObjects(ctx, [&roots](ObjectFile* file) {
            roots.push_back(file);
        });
        roots.erase(roots.begin());
    }
}