import ReactDOM from "react-dom/client";
import { ConfigProvider } from "antd";
import { Theme } from "theme/customAntdTheme";

import { MainWidget } from "components/mainWidget";

import "./theme/global.less";

import reportWebVitals from "./utils/reportWebVitals";

const root = ReactDOM.createRoot(document.getElementById("root") as HTMLElement);

root.render(
  <ConfigProvider theme={Theme}>
      <MainWidget />
  </ConfigProvider>
);

reportWebVitals();
