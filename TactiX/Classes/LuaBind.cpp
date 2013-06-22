/*
** Lua binding: TactiX
** Generated automatically by tolua++-1.0.92 on Mon Jun 10 21:36:48 2013.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_TactiX_open (lua_State* tolua_S);

#include "LuaCocos2d.h"
#include "Weapon.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* Open function */
TOLUA_API int tolua_TactiX_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"WeaponKindNone",WeaponKindNone);
  tolua_constant(tolua_S,"WeaponKindSword",WeaponKindSword);
  tolua_constant(tolua_S,"WeaponKindSpear",WeaponKindSpear);
  tolua_constant(tolua_S,"WeaponKindBow",WeaponKindBow);
  tolua_constant(tolua_S,"WeaponTypeNone",WeaponTypeNone);
  tolua_constant(tolua_S,"WeaponTypeSolid",WeaponTypeSolid);
  tolua_constant(tolua_S,"WeaponTypeLiquid",WeaponTypeLiquid);
  tolua_constant(tolua_S,"WeaponTypePlasma",WeaponTypePlasma);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_TactiX (lua_State* tolua_S) {
 return tolua_TactiX_open(tolua_S);
};
#endif

