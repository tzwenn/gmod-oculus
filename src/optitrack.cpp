#include <GarrysMod/Lua/Interface.h>

using namespace GarrysMod::Lua;

#define registerFunction(Func) \
	state->luabase->PushSpecial( GarrysMod::Lua::SPECIAL_GLOB );\
	state->luabase->PushString(#Func);\
	state->luabase->PushCFunction(Func);\
	state->luabase->SetTable(-3);

static int skelCallbackRef = 0;

static void freeReference(lua_State *state)
{
	if (skelCallbackRef)
		LUA->ReferenceFree(skelCallbackRef);

	skelCallbackRef = 0;
}

static void sendSkeletonData(lua_State *state, const char *string)
{
	LUA->ReferencePush(skelCallbackRef);
	LUA->PushString(string);
	LUA->Call(1, 0);
}

int ReceiveOptitrackData(lua_State *state)
{
	if (!skelCallbackRef)
		return 0;

	sendSkeletonData(state, "How fascinating");

	return 0;
}

int setSkeletonCallback(lua_State *state)
{
	LUA->CheckType(1, Type::FUNCTION);
	freeReference(state);
	LUA->Push(1);
	
	skelCallbackRef = LUA->ReferenceCreate();

	return 0;
}


//
// Called when you module is opened
//
GMOD_MODULE_OPEN()
{
	registerFunction(setSkeletonCallback)
	registerFunction(ReceiveOptitrackData)
	return 0;
}

//
// Called when your module is closed
//
GMOD_MODULE_CLOSE()
{
	freeReference(state);
	return 0;
}
