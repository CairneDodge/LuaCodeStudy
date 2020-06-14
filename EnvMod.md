# Global,env,registry
  Global表存放在lua_state结构体中, env表存放在Closure结构体中，registry表存放在global_State结构体中
  函数的env表创建，如果不是内嵌函数，直接返回G表，否则返回父函数的env表
  
  
  创建模块时会创建一个表，该表挂载在registry["_LOADED"]，_G[模块名]下，
  
# 热更新
  function require_ex(_mname)
    if package.loaded[_mname] then
      print()
    end
    package.loaded[_mname]=nil
    require(_mname)
  end
