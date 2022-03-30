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
> 2021-11-07 日: 完成初版

[原文地址](https://github.com/wax5798/blog)

# VUE 学习之从一个简单的网站开始

## 写在前面
由于工作要求，需要维护以及简单开发公司产品的网页管理页面。所以需要学习一些前端以及后台的基本知识，并不会太深入。在学习的过程中，对用到的知识点做一下整理

作为学习的案例，本文介绍一个简单的网站搭建。后台使用 node.js 实现，所以本文会涉及到 node.js、npm、vue 等工具的使用

开发环境： Ubuntu 20.04  
开发工具： vim（没有使用 IDE）

## NPM
先贴一个 [NPM 的官方中文文档](https://www.npmjs.cn/)  
再贴一个 [NPM 博文](https://blog.csdn.net/qq_38490457/article/details/109739444#commentBox)

#### NPM 简介
NPM 可以简单的理解为 Node.js 标准的软件包管理器，常用在如下几种场景：
- 允许用户从NPM服务器下载别人编写的第三方包到本地使用
- 允许用户从NPM服务器下载并安装别人编写的命令行程序到本地使用
- 允许用户将自己编写的包或命令行程序上传到NPM服务器供别人使用

可以使用 `sudo apt-get install npm` 安装 npm

#### NPM 常用命令
升级 npm
> npm -g install npm

修改镜像源
> npm config set registry http://registry.npm.taobao.org  

还原镜像源
> npm config set registry https://registry.npmjs.org/

查看镜像源
> npm config get registry

安装与卸载软件软件包
> npm install/uninstall package-name  
> 加上 -g 参数表示全局安装/卸载  
> 加上 --save，则会更新 package.json 文件的 dependencies (package.json 文件会在后续说明)  
> 加上 --save-dev，则会更新 package.json 文件的 devDependencies  
> 可以安装指定版本，如 npm install -g webpack@4.16.4  
> 本地安装在当前文件树的 node_modules 子文件夹下，全局安装的位置可以通过命令 `npm root -g` 查看  
> 至于安装了这些包怎么使用，会在后续 VUE 和 NODEJS 中看到

软件包的查看
> 查看所有已安装的软件包，npm list [-g] [--depth=num]  
> 列出软件包所有以前的版本，如 npm view webpack versions  

软件包的更新
> npm update [-g] [package-name]  

命令行型模块的运行
> 如果全局安装命令行型模块，直接在终端运行命令即可  
> 如果局部安装命令行型模块，需要在 package.json 同级目录运行: node_modules/.bin/[cmd]  
> 想直接运行局部安装的命令，可以把 node_modules/.bin 添加在 PATH 中，然后在 package.json 同级目录下执行命令

#### package.json 文件
package.json 文件是项目的清单，它保存了当前项目的配置以及依赖的软件和版本等信息

一个简单的实例如下:
```
{
  "name": "vue_web",
  "version": "0.1.0",
  "private": true,
  "scripts": {
    "serve": "vue-cli-service serve",
    "build": "vue-cli-service build",
    "lint": "vue-cli-service lint"
  },
  "dependencies": {
    "axios": "^0.24.0",
    "core-js": "^3.6.5",
    "downloadjs": "^1.4.7",
    "element-ui": "^2.15.6",
    "vue": "^2.6.11"
  },
  "devDependencies": {
    "@vue/cli-plugin-babel": "~4.5.0",
    "@vue/cli-plugin-eslint": "~4.5.0",
    "@vue/cli-service": "~4.5.0",
    "babel-eslint": "^10.1.0",
    "eslint": "^6.7.2",
    "eslint-plugin-vue": "^6.2.2",
    "vue-template-compiler": "^2.6.11"
  },
  "eslintConfig": {
    "root": true,
    "env": {
      "node": true
    },
    "extends": [
      "plugin:vue/essential",
      "eslint:recommended"
    ],
    "parserOptions": {
      "parser": "babel-eslint"
    },
    "rules": {}
  },
  "browserslist": [
    "> 1%",
    "last 2 versions",
    "not dead"
  ]
}
```

其中的关键字解释:
> name 设置了应用程序/软件包的名称  
> version 表明了当前的版本  
> description 是应用程序/软件包的简短描述  
> main 设置了应用程序的入口点  
> private 如果设置为 true，则可以防止应用程序/软件包被意外地发布到 npm  
> scripts 定义了一组可以运行的 node 脚本，可以通过 npm run [cmd] 运行  
> dependencies 设置了作为依赖安装的 npm 软件包的列表，这是生产环境下依赖的模块  
> devDependencies 在开发环境下依赖的模块，生产环境不会被打入包内  
> engines 设置了此软件包/应用程序在哪个版本的 Node.js 上运行  
> browserslist 用于告知要支持哪些浏览器（及其版本）  
> 还有一些特有的属性，它们是命令特有的，如 eslintConfig  

package.json 中还规定了更新规则:
> `^:` 如果写入的是 ^0.13.0，则当运行 npm update 时，会更新到补丁版本和次版本：即 0.13.1、0.14.0、依此类推  
> `~:` 如果写入的是 〜0.13.0，则当运行 npm update 时，会更新到补丁版本：即 0.13.1 可以，但 0.14.0 不可以  
> `>:` 接受高于指定版本的任何版本  
> `>=:` 接受等于或高于指定版本的任何版本  
> `<=:` 接受等于或低于指定版本的任何版本  
> `<:` 接受低于指定版本的任何版本  
> `=:` 接受确切的版本  
> `-:` 接受一定范围的版本。例如：2.1.0 - 2.6.2  
> `||:` 组合集合。例如 `< 2.1 || > 2.6`  

#### package-lock.json 文件
该文件旨在跟踪被安装的每个软件包的确切版本，以便产品可以以相同的方式被 100％ 复制

## VUE
先贴一个 [VUE 的官方指导网站](https://cn.vuejs.org/v2/guide/)  
再贴一个 [VUE 的学习建议网站](https://blog.csdn.net/zhenghongcs/article/details/105631162)  
再贴一个 [Vue CLI 的官方网站](https://cli.vuejs.org/zh/guide/)  

## NODEJS
先贴一个 [NODEJS API](http://nodejs.cn/api/)

#### NODEJS 简介
简单的说 Node.js 就是运行在服务端的 JavaScript。

Node.js 是一个基于Chrome JavaScript 运行时建立的一个平台

#### NODEJS 代码的调试
nodejs 作为后台程序，不能像前端一样直接通过浏览器进行调试。以下是可以单步调试 nodejs 的方法

> step1: 在 chrome 打开 chrome://inspect  
> step2: 在终端运行: node --inspect-brk ./test.js  
> step3: 在 chrome 点击 "inspect" 开始调试

## 搭建前端

#### 创建一个默认的 demo
```
$ sudo npm install @vue/cli -g  // 安装 vue 终端命令
$ vue create vue_web            // 创建项目，创建过程中选择默认配置即可
$ cd vue_web
$ npm run serve                 // Compiles and hot-reloads for development
```

关于 demo 的使用说明，可以查看 README.md

#### 对 demo 进行调整
axios 是一个基于Promise 用于浏览器和 nodejs 的 HTTP 客户端，与后台通信会使用到，安装命令如下
```
$ npm install axios --save
```

添加 src/utils/request.js 文件，里面包含了 axios 的使用
```
import axios from 'axios';

const URL_BASE = "http://127.0.0.1:3000";

const AXIOS_TEST_URL = "/axios/test";


let get = (base, api, success, error) => {
  axios.get(base + api).then((res) => {
    if (res && res.data && res.status === 200) {
      success(res.data);
    } else {
      error(res.status, res.data);
    }
  }).catch((err) => {
    error(err.response.status, err.message);
  });
};

let post = (base, api, data, success, error) => {
  axios.post(base + api, data).then((res) => {
    if (res && res.data && res.status === 200) {
      success(res.data);
    } else {
      error(res.status, res.message);
    }
  }).catch((err) => {
    error(err.response.status, err.message);
  });
};

let axiosGetTest = (success, error) => {
  get(URL_BASE, AXIOS_TEST_URL, success, error);
};

let axiosPostTest = (data, success, error) => {
  post(URL_BASE, AXIOS_TEST_URL, data, success, error);
};

export { axiosGetTest, axiosPostTest };
```

安装 ui 框架
```
$ npm install element-ui --save
```

为了使 ui 框架生效，添加 src/plugins/element.js 文件，并在 src/main.js 中 import
```
import Vue from 'vue'
import Element from 'element-ui'
import 'element-ui/lib/theme-chalk/index.css'

Vue.use(Element)
```

## 搭建后台
#### 创建一个最简 demo
```
$ npm install express-generator -g      // 安装 express 命令行工具，可以快速创建一个应用开发框架
$ npm install express -g                // express-generator 需要使用
$ express nodejs_server                 // 创建一个 nodejs 的后台 demo
```

在 nodejs_server 下添加 .gitignore 文件
```
*.swp

node_modules
package-lock.json
```

#### 对 demo 进行调整
解决跨域访问问题(Reason: CORS header ‘Access-Control-Allow-Origin’ missing)，在 app.js 中添加如下代码
```
app.all('*', function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Headers", "X-Requested-With, content-type");
  res.header("Access-Control-Allow-Methods","PUT,POST,GET,DELETE,OPTIONS");
  res.header("Content-Type", "application/json;charset=utf-8");
  next();
});
```

删除 app.js 中对 http-errors 的使用，否则接受 POST 请求时，会报错(Reason: CORS preflight response did not succeed)

添加路由解析
```
const test = require("./modules/test");

app.get("/axios/test", test.getMethodTest);
app.post("/axios/test", test.postMethodTest);
```

其中 ./modules/test.js 的内容如下
```
let getMethodTest = (req, res) => {
  res.send("get method test success");
  res.end();
};

let postMethodTest = (req, res) => {
  let data = req.body;

  console.log("get req: " + data);

  res.send("post method test success");
  res.end();
};

module.exports = {getMethodTest, postMethodTest};
```

需要注意跨域访问的问题: https://blog.csdn.net/dyxcome/article/details/98474601
