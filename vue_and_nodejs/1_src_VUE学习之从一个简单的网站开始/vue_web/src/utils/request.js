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
