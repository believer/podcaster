open ReactNative;
open ApolloHooks;

module PodcastQuery = [%graphql
  {|
    query PodcastQuery($id: ID!) {
      podcast(id: $id) {
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
let make =
    (~navigation, ~route: ReactNavigation.Core.route(Navigators.M.params)) => {
  let id =
    switch (route.params) {
    | Some({id}) => id
    | None => ""
    };
  let {Player.setEpisode} = Player.usePlayer();
  let (simple, _full) =
    useQuery(
      ~variables=PodcastQuery.makeVariables(~id, ()),
      PodcastQuery.definition,
    );

  switch (simple) {
  | Data(data) =>
    switch (data##podcast) {
    | Some(podcast) =>
      <SafeAreaView>
        <Text> {React.string(podcast##title)} </Text>
        <FlatList
          data=podcast##episodes
          keyExtractor={(episode, _) => episode##id}
          renderItem={episode =>
            <TouchableOpacity
              onPress={_ => {
                Player.Episode.make(~episode=episode##item, ~podcast)
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
    | None => React.null
    }
  | NoData
  | Error(_) => React.null
  | Loading => <ActivityIndicator />
  };
};
