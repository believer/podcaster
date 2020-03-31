[@react.component]
let make = () => {
  let (query, setQuery) = React.useState(() => None);
  let {currentTrack, playState, playbackRate, setPlaybackRate}: Player.Context.t =
    Player.usePlayer();

  let updatePlaybackRate = rate => setPlaybackRate(rate);

  <>
    <div
      className="w-screen h-screen flex flex-col justify-center items-center">
      <input
        placeholder="search"
        onChange={event => {
          let value = event->ReactEvent.Form.target##value;
          setQuery(_ => Some(value));
        }}
        value={query->Belt.Option.getWithDefault("")}
      />
      <SearchResults query setQuery />
      {switch (playState) {
       | NoTrack => React.null
       | Loading => <div> {React.string("Loading")} </div>
       | Ready({player, duration}) =>
         <>
           {switch (currentTrack) {
            | Some({cover, description, title}) =>
              <div>
                {switch (cover) {
                 | Some(src) => <img className="w-20 h-20 rounded" src />
                 | None => React.null
                 }}
                <div> {React.string(title)} </div>
                <div
                  className="mt-8"
                  dangerouslySetInnerHTML={"__html": description}
                />
              </div>
            | None => React.null
            }}
           <PlayerPosition player duration />
           <Layout.Stack
             align={Some(Layout.Center)} space={Some(Layout.Large)}>
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
         </>
       }}
    </div>
  </>;
};
