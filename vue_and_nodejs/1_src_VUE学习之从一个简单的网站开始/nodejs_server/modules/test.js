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

module.exports = {getMethodTest, postMethodTest};
