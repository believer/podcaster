[@react.component]
let make = (~duration, ~player: Audio.t) => {
  let (currentTime, setCurrentTime) = React.useState(() => 0.0);

  React.useEffect0(() => {
    let timeUpdate = _event => {
      setCurrentTime(_ => player.currentTime *. 1000.);
    };

    player->Audio.addListener("timeupdate", timeUpdate);

    Some(_ => {player->Audio.removeListener("timeupdate", timeUpdate)});
  });

  <div className="flex items-center">
    <div className="font-variant-tabular">
      {currentTime->Duration.make->React.string}
    </div>
    <div className="w-56 h-2 bg-gray-300 mx-2 rounded overflow-hidden">
      <div
        className="w-16 h-2 rounded bg-blue-500"
        style={ReactDOMRe.Style.make(
          ~width=(currentTime /. duration *. 100.)->Belt.Float.toString ++ "%",
          (),
        )}
      />
    </div>
    <div className="font-variant-tabular">
      {duration->Duration.make->React.string}
    </div>
  </div>;
};
