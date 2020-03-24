type t =
  | Ready({
      player: Audio.t,
      duration: float,
    })
  | Loading;

let usePlayer = url => {
  let (playerState, setPlayerState) = React.useState(() => Loading);

  React.useEffect0(() => {
    let player = Audio.make(url);
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
