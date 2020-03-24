module Audio = {
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
  external removeListener: (t, Js.t('a) => unit) => unit =
    "removeEventListener";
};

module Counter = {
  [@react.component]
  let make = (~duration, ~player: Audio.t) => {
    let (currentTime, setCurrentTime) = React.useState(() => 0.0);

    React.useEffect0(() => {
      let timeUpdate = _event => {
        setCurrentTime(_ => player.currentTime *. 1000.);
      };

      player->Audio.addListener("timeupdate", timeUpdate);

      Some(_ => {player->Audio.removeListener(timeUpdate)});
    });

    <div className="flex items-center">
      <div className="font-variant-tabular">
        {currentTime->Duration.make->React.string}
      </div>
      <div className="w-56 h-2 bg-gray-300 mx-2 rounded overflow-hidden">
        <div
          className="w-16 h-2 rounded bg-blue-500"
          style={ReactDOMRe.Style.make(
            ~width=
              (currentTime /. duration *. 100.)->Belt.Float.toString ++ "%",
            (),
          )}
        />
      </div>
      <div className="font-variant-tabular">
        {duration->Duration.make->React.string}
      </div>
    </div>;
  };
};

module Player = {
  type t =
    | Ready({
        player: Audio.t,
        duration: float,
      })
    | Loading;

  let usePlayer = url => {
    let (playerState, setPlayerState) = React.useState(() => Loading);
    let player = Audio.make(url);

    React.useEffect0(() => {
      let canPlay = _event => {
        setPlayerState(_ =>
          Ready({player, duration: player.duration *. 1000.})
        );
      };

      player->Audio.addListener("canplay", canPlay);

      Some(_ => {player->Audio.removeListener(canPlay)});
    });

    playerState;
  };
};

[@react.component]
let make = () => {
  let playerState =
    Player.usePlayer(
      "https://dts.podtrac.com/redirect.mp3/rss.art19.com/episodes/4873dad1-e9af-4e46-8dad-ba01d6f6cba8.mp3",
    );

  switch (playerState) {
  | Loading => <div> {React.string("Loading")} </div>
  | Ready({player, duration}) =>
    <div
      className="w-screen h-screen flex flex-col justify-center items-center">
      <Counter player duration />
      <div className="flex flex-col items-center">
        <div>
          <button
            className="text-lg text-gray-800"
            onClick={_ => player->Audio.play}>
            {React.string("Play")}
          </button>
          <button
            className="ml-2 text-lg text-gray-800"
            onClick={_ => player->Audio.pause}>
            {React.string("Pause")}
          </button>
        </div>
        <div>
          <button
            className="text-sm text-gray-600"
            onClick={_ => player.playbackRate = 1.0}>
            {React.string("1x")}
          </button>
          <button
            className="ml-2 text-sm text-gray-600"
            onClick={_ => player.playbackRate = 1.5}>
            {React.string("1.5x")}
          </button>
          <button
            className="ml-2 text-sm text-gray-600"
            onClick={_ => player.playbackRate = 2.0}>
            {React.string("2x")}
          </button>
        </div>
      </div>
    </div>
  };
};
