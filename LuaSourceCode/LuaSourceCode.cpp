#include <stdio.h>

extern "C" {

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

}
int main()
{
    lua_State* L = luaL_newstate();
    lua_pushnil(L);
    int type = lua_type(L, -1);
    printf("nil type = %d \n", type);
    if (lua_isnil(L,-1))
    {
        printf("---nil---\n");
    }

    lua_pushboolean(L,0);
    type = lua_type(L, -1);
    lua_isboolean(L, -1);

    lua_pushlightuserdata(L, NULL);

    lua_newuserdata(L, 1024);

    lua_newtable(L);
    type = lua_type(L, -1);
    printf("table type = %d \n", type);

    luaL_openlibs(L);   //打开所有标准库
    int ret = luaL_loadfile(L, "xx.lua");
    if (ret != LUA_OK)
    {
        const char* err = lua_tostring(L, -1);
        printf("----loadfile error = %s\n",err);
    }

    lua_getglobal(L, "var"); 
    int var = lua_tonumber(L, -1);
    printf("var = %d\n", var);
    lua_pushnumber(L, 10);
    lua_setglobal(L, "var");
    lua_getglobal(L, "f");
    lua_pcall(L, 0, 0, 0);

    // 读取table
    lua_getglobal(L, "t");
    lua_getfield(L, 1, "a");  //从索引为1的位置(table)获取t.a，并压栈
    lua_getfield(L, 1, "b");
    lua_getfield(L, -1, "c"); //从索引为-1的位置(栈顶)获取t.c，并压栈

    // 修改table
    lua_settop(L, 1); //设置栈的位置为1，此时栈上只剩一个元素t
    lua_pushnumber(L, 10);
    lua_setfield(L, 1, "a"); //t.a=10
    lua_pushstring(L, "hello c");
    lua_setfield(L, 1, "e"); //t.e="hello c"

    //新建一个table
    lua_settop(L, 0); //清空栈
    lua_newtable(L); //创建一个table
    lua_pushboolean(L, 0);
    lua_setfield(L, 1, "new_a");
    lua_pushboolean(L, 1);
    lua_setfield(L, 1, "new_b");
}

//7 #define TYPE_BOOLEAN 1
//8 #define TYPE_NUMBER 2
//9 #define TYPE_STRING 3
//10
//11 static int ladd(lua_State * L) {
//    12     double op1 = luaL_checknumber(L, -2);
//    13     double op2 = luaL_checknumber(L, -1);
//    14     lua_pushnumber(L, op1 + op2);
//    15     return 1;
//    16
//}
//17
//18 static int lsub(lua_State * L) {
//    19     double op1 = luaL_checknumber(L, -2);
//    20     double op2 = luaL_checknumber(L, -1);
//    21     lua_pushnumber(L, op1 - op2);
//    22     return 1;
//    23
//}
//24
//25 static int lavg(lua_State * L) {
//    26     double avg = 0.0;
//    27     int n = lua_gettop(L);
//    28     if (n == 0) {
//        29         lua_pushnumber(L, 0);
//        30         return 1;
//        31
//    }
//    32     int i;
//    33     for (i = 1; i <= n; i++) {
//        34         avg += luaL_checknumber(L, i);
//        35
//    }
//    36     avg = avg / n;
//    37     lua_pushnumber(L, avg);
//    38     return 1;
//    39
//}
//40
//41 static int fn(lua_State * L) {
//    42     int type = lua_type(L, -1);
//    43     printf("type = %d\n", type);
//    44     if (type == LUA_TBOOLEAN) {
//        45         lua_pushvalue(L, lua_upvalueindex(TYPE_BOOLEAN));
//        46
//    }
//    else if (type == LUA_TNUMBER) {
//        47         lua_pushvalue(L, lua_upvalueindex(TYPE_NUMBER));
//        48
//    }
//    else if (type == LUA_TSTRING) {
//        49         lua_pushvalue(L, lua_upvalueindex(TYPE_STRING));
//        50
//    }
//    51     return 1;
//    52
//}
//53
//54 int luaopen_mylib(lua_State * L) {
//    55     luaL_Reg l[] = {
//    56         {"add", ladd},
//    57         {"sub", lsub},
//    58         {"avg", lavg},
//    59         {NULL, NULL},
//    60 };
//    61     luaL_newlib(L, l);
//    62
//        63     lua_pushliteral(L, "BOOLEAN");
//    64     lua_pushliteral(L, "NUMBER");
//    65     lua_pushliteral(L, "STRING");
//    66     lua_pushcclosure(L, fn, 3);
//    67
//        68     lua_setfield(L, -2, "fn");
//    69     return 1;
//    70
//}

