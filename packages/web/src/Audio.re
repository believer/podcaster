type t = {
  currentTime: float,
  duration: float,
  mutable playbackRate: float,
};

[@bs.new] external make: string => t = "Audio";

[@bs.send] external play: t => unit = "play";
[@bs.send] external pause: t => unit = "pause";

[@bs.send]
external addListener: (t, string, Js.t('a) => unit) => unit =
  "addEventListener";

[@bs.send]
external removeListener: (t, string, Js.t('a) => unit) => unit =
  "removeEventListener";
