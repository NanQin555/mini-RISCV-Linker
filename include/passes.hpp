#pragma once
class Context;
class passes {
public:
    void ResolveSymbols(Context*);      
    void MarkLiveObjects(Context*);
};


