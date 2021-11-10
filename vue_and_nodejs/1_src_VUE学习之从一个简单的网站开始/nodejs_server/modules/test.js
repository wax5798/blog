var JSZip = require("jszip");
const fs = require("fs");

let getMethodTest = (req, res) => {
  res.send("get method test success");
  res.end();
};

let postMethodTest = (req, res) => {
  let body = req.body;

  console.log("get req: " + body.data);

  res.send("post method test success");
  res.end();
};

const gnss_log_file = "/home/osrc/gitPro/blog/vue_and_nodejs/1_src_VUE学习之从一个简单的网站开始/nodejs_server/gnss.log";
const gnss_log_file1 = "/home/osrc/gitPro/blog/vue_and_nodejs/1_src_VUE学习之从一个简单的网站开始/nodejs_server/gnss.log.1";

let downloadMethodTest = (req, res) => {
  try {
    var zip = new JSZip();
    const folder = zip.folder("gnss_log");

    if (fs.existsSync(gnss_log_file)) {
      folder.file("gnss.log", fs.readFileSync(gnss_log_file, "utf8"));
    }

    if (fs.existsSync(gnss_log_file1)) {
      folder.file("gnss.log.1", fs.readFileSync(gnss_log_file1, "utf8"));
    }

    zip.generateAsync({type: 'base64', compression: "DEFLATE", compressionOptions: {level: 9}}).then(content => {
      res.send(content);
    }).catch(err => {
      console.log("error: " + err);
      res.status(404).send();
      res.end();
    });
  } catch(err) {
    console.log("getGnssLog err: " + err + ".");
    res.status(404).send();
    res.end();
  }
};

module.exports = {getMethodTest, postMethodTest, downloadMethodTest};
