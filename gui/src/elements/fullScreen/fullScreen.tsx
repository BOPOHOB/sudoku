import type { FC, ReactNode } from "react";
import { Empty, Spin } from "antd";

import cn from "./style.module.less";

const FullScreen: FC<{ children: ReactNode }> = ({ children }) => {
  return <div className={cn.center}>{children}</div>;
};

const FullScreenLoader: FC<{ children?: ReactNode }> = ({ children }) => (
  <FullScreen>
    <Spin tip={children ?? "Загрузка"} size="large" />
  </FullScreen>
);

const FullScreenEmpty: FC<{ children: ReactNode }> = ({ children }) => (
  <FullScreen>
    <Empty style={{ maxWidth: 700 }} description={children} />
  </FullScreen>
);

const FullScreenNotFound: FC<{ children: ReactNode }> = ({ children }) => (
  <FullScreen>
    <Empty image="тут будет 404" style={{ maxWidth: 700 }} description={children} />
  </FullScreen>
);

export { FullScreenEmpty, FullScreenLoader, FullScreenNotFound };
