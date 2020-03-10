module Video = {
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
      ~ref: React.Ref.t('ref)=?,
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
