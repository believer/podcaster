[@react.component]
let make = () => {
  let (playbackRate, setPlaybackRate) = React.useState(_ => 1.0);
  let (query, setQuery) = React.useState(() => "");

  let playerState =
    Player.usePlayer(
      "https://dts.podtrac.com/redirect.mp3/rss.art19.com/episodes/4873dad1-e9af-4e46-8dad-ba01d6f6cba8.mp3",
    );

  switch (playerState) {
  | Loading => <div> {React.string("Loading")} </div>
  | Ready({player, duration}) =>
    let updatePlaybackRate = rate => {
      player.playbackRate = rate;
      setPlaybackRate(_ => rate);
    };

    <div
      className="w-screen h-screen flex flex-col justify-center items-center">
      <input
        onChange={event => {
          let value = event->ReactEvent.Form.target##value;
          setQuery(_ => value);
        }}
      />
      <SearchResults query />
      <PlayerPosition player duration />
      <Layout.Stack align={Some(Layout.Center)} space={Some(Layout.Large)}>
        <Layout.Columns space={Some(Layout.Small)}>
          <Button.PlayerControl onClick={_ => player->Audio.play}>
            {React.string("Play")}
          </Button.PlayerControl>
          <Button.PlayerControl onClick={_ => player->Audio.pause}>
            {React.string("Pause")}
          </Button.PlayerControl>
        </Layout.Columns>
        <Layout.Columns space={Some(Layout.Small)}>
          <Button.SmallPlayerControl
            isActive={playbackRate === 1.0}
            onClick={_ => updatePlaybackRate(1.0)}>
            {React.string("1x")}
          </Button.SmallPlayerControl>
          <Button.SmallPlayerControl
            isActive={playbackRate === 1.5}
            onClick={_ => updatePlaybackRate(1.5)}>
            {React.string("1.5x")}
          </Button.SmallPlayerControl>
          <Button.SmallPlayerControl
            isActive={playbackRate === 2.0}
            onClick={_ => updatePlaybackRate(2.0)}>
            {React.string("2x")}
          </Button.SmallPlayerControl>
        </Layout.Columns>
      </Layout.Stack>
    </div>;
  };
};
