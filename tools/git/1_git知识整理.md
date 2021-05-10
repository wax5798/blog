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
> 2021-04-26 一: 完成初版

[原文地址](https://github.com/wax5798/blog/blob/master/tools/git/1_git%E7%9F%A5%E8%AF%86%E6%95%B4%E7%90%86.md)

# git 知识整理

## 前言
使用 git，经常有一些命令，偶尔会用到，但是又不常用到，这就造成每次用的时候都需要百度。所以干脆对这些命令做一下整理，方便后续查阅

## 全局配置与当前项目配置
git 的全局配置一般保存在 ~/.gitconfig 中，而当前项目配置一般保存在 .git/config 中

使用 git config 命令查看或设置配置信息，--global 表示全局配置，否则为本地配置

- 查看当前配置信息:	`git config [--global] --list`  
- 查看邮箱配置:		`git config [--global] user.email`  
- 配置用户名:			`git config [--global] user.name "wax5798"`  
- 配置邮箱:			`git config [--global] user.email "123456@qq.com"`  
- 记住用户名和密码：	`git config [--global] credential.helper store`  
- 解决 git status 乱码: `git config --global core.quotepath false`  

## 关于 git 补丁
#### 方法一: git diff + git apply
- 生成 patch: `git diff [前一个提交] [目标提交] [--cache] > my.patch`  
- 应用 patch: `git apply my.patch`  

这种方式，apply 之后需要手动 add 和 commit  

#### 方法二: git format-patch + git am 打单个补丁
- 生成 patch: `git format-patch -1 commitId` （提取单个 commit）  
- 应用 patch: `git am patchName` （一般建议 git am 应用补丁之前使用 git am --abort）  

这中方式会将提交信息直接打进去

#### 方法三: git format-patch + git am 打多个补丁
- 生成 patch: `git format-patch commitId` （生成 commit 之后的所有补丁）  
- 应用 patch: `git am *.patch` （应用所有 patch）  

有冲突的话解决冲突，然后git add对应文件，git am --resolve。不能解决想后面再说就git am --skip，具体使用方法参考git am --help

#### 检查 patch
- 先检查patch文件： `git apply --stat newpatch.patch`  
- 检查能否应用成功：`git apply --check newpatch.patch`  
