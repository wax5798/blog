<head><meta charset="UTF-8"></head>
<style>
h1 {
    text-align: center;
    border-left: 5px solid #e86422;
    border-right: 5px solid #e86422;
}
h2 {
    border-left: 5px solid #ff7f00;
    padding-left: 10px;
}
h3 {
    border-left: 5px solid #e86422;
    padding-left: 8px;
}
h4 {
    border-left: 3px solid #f0a000;
    padding-left: 5px;
}
</style>

Release log:  
> 2018-02-01 四: 完成初版  
> 2021-04-18 日: 更新格式

[原文地址](https://github.com/wax5798/blog/blob/master/config/1_Ubuntu%E4%BD%BF%E7%94%A8xkb%E4%BF%AE%E6%94%B9%E6%8C%89%E9%94%AE%E6%98%A0%E5%B0%84.md)

# Ubuntu使用xkb修改按键映射

## 目的
由于使用 vim 时，经常要用到 ESC 键。奈何 ESC 键距离太远，操作起来很不方便，所以想把 ESC 键映射到 CAPS 键，而以前的 CAPS 则映射到右 CTRL  
最初的想法是使用 xmodmap，但配置好了之后才发现 xmodmap 与 fcitx 有兼容性问题（ibus 也有同样的问题）。
关于这一点还专门到 fcitx 的 github 上提了 issue，但得到的回复是， **不建议使用 xmodmap，建议使用 xkb**  
记录下我的配置步骤，备忘

## 步骤
1、查看当前键盘布局 `setxkbmap -print`
```
xkb_keymap {
    xkb_keycodes  { include "evdev+aliases(qwerty)" };
    xkb_types     { include "complete"  };  
    xkb_compat    { include "complete"  };  
    xkb_symbols   { include "pc+us+inet(evdev)" };
    xkb_geometry  { include "pc(pc105)" };
};
```
`xkb_symbols` 属性后面的 pc 即我们需要修改的文件，**修改前务必做好备份**

2、使用编辑器打开`/usr/share/X11/xkb/symbols/pc`，修改如下内容
```
- key <CAPS> {    [ Caps_Lock     ]   };                                                                 
+ key <CAPS> {    [ Escape        ]   };  
 .
 .
 .
- key <RCTL> {    [ Control_R     ]   };  
+ key <RCTL> {    [ Caps_Lock     ]   };  
```

3、保存文件并重新登录桌面
