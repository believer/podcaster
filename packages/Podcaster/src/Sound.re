open ReactNative;

module ReactNativeVideo = {
  type source = {uri: string};

  type onLoad = {duration: float};

  type onProgress = {
    currentTime: float,
    playableDuration: float,
    seekableDuration: float,
  };

  [@react.component] [@bs.module "react-native-video"]
  external make:
    (
      ~source: source,
      ~ref: ReactDOMRe.Ref.t=?,
      ~audioOnly: bool,
      ~ignoreSilentSwitch: string,
      ~playInBackground: bool,
      ~rate: float,
      ~paused: bool,
      ~poster: string,
      ~onProgress: onProgress => unit,
      ~onLoad: onLoad => unit,
      ~style: ReactNative.Style.t
    ) =>
    React.element =
    "default";
};

[@react.component]
let make =
  React.forwardRef(
    (
      ~uri,
      ~onLoad: ReactNativeVideo.onLoad => unit,
      ~onProgress: ReactNativeVideo.onProgress => unit,
      ~rate,
      ~poster,
      ~paused,
      ref,
    ) => {
    <ReactNativeVideo
      ref=?{ref->Js.Nullable.toOption->Belt.Option.map(ReactDOMRe.Ref.domRef)}
      ignoreSilentSwitch="ignore"
      playInBackground=true
      source={uri: uri}
      audioOnly=true
      onLoad
      onProgress
      paused
      rate
      style=Style.(
        style(~borderRadius=20., ~height=300.->dp, ~width=300.->dp, ())
      )
      poster
    />
  });
