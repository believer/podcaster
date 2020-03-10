open ReactNative;
open ApolloHooks;

module PodcastQuery = [%graphql
  {|
  query PodcastQuery {
    podcast(id: "278981407") {
      image
      link
      title
      description
      episodes {
        date
        description
        duration
        id
        title
        url
      }
    }
  }
|}
];

[@react.component]
let make = (~navigation, ~route as _) => {
  let {Player.setEpisode} = Player.usePlayer();
  let (simple, _full) = useQuery(PodcastQuery.definition);

  switch (simple) {
  | Loading => <ActivityIndicator size=ActivityIndicator.Size.large />
  | Data(data) =>
    switch (data##podcast) {
    | Some(podcast) =>
      <SafeAreaView>
        <Text> {React.string(podcast##title)} </Text>
        <FlatList
          data={podcast##episodes}
          keyExtractor={(episode, _) => episode##id}
          renderItem={episode =>
            <TouchableOpacity
              onPress={_ => {
                Player.Episode.make(episode##item, podcast##image)
                ->setEpisode;

                navigation->Navigators.RootStack.Navigation.navigate(
                  "Player",
                );
              }}
              style=Style.(style(~marginBottom=8.->dp, ()))>
              <Text> {React.string(episode##item##title)} </Text>
            </TouchableOpacity>
          }
        />
      </SafeAreaView>
    | None => <Text> {React.string("No user")} </Text>
    }
  | NoData
  | Error(_) => React.null
  };
};
