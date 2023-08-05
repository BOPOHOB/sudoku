const CracoLessPlugin = require("craco-less");

module.exports = {
  devServer: {
    historyApiFallback: true,
    proxy: {
      "/api": {
        target: "http://localhost:3003",
      },
    },
  },
  plugins: [
    {
      plugin: CracoLessPlugin,
      options: {
        lessLoaderOptions: {
          lessOptions: {
            modifyVars: {
              ...require("./src/theme/global.js"),
            },
            javascriptEnabled: true,
          },
        },
      },
    },
  ],
};
