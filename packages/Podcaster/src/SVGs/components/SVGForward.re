[@react.component] [@bs.module "./SVGForward.js"]
external make:
  (
    ~width: ReactFromSvg.Size.t=?,
    ~height: ReactFromSvg.Size.t=?,
    ~fill: string=?
  ) =>
  React.element =
  "default";
