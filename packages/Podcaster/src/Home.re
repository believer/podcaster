open ReactNative;
open ApolloHooks;

module SearchMutation = [%graphql
  {|
  mutation SearchMutation($query: String!) {
    search(input: { query: $query }) {
      id
      artist
      artwork
      url
      name
    }
  }
|}
];

[@react.component]
let make = (~navigation, ~route as _) => {
  let (searchResults, setSearchResults) = React.useState(() => [||]);

  let (searchMutation, _simple, _full) =
    useMutation(SearchMutation.definition);

  <SafeAreaView>
    <TextInput
      placeholder="Search"
      onChangeText={query => {
        Js.Promise.(
          searchMutation(
            ~variables=SearchMutation.makeVariables(~query, ()),
            (),
          )
          |> then_((result: ApolloHooks.Mutation.result(SearchMutation.t)) => {
               switch (result) {
               | Data(data) => setSearchResults(_ => data##search)
               | Error(_)
               | NoData => ()
               };

               resolve();
             })
          |> ignore
        )
      }}
    />
    <FlatList
      data=searchResults
      keyExtractor={(show, _) => show##id}
      renderItem={show =>
        <TouchableOpacity
          onPress={_ => {
            navigation->Navigators.RootStack.Navigation.navigateWithParams(
              "Podcast",
              {id: show##item##id},
            )
          }}
          style=Style.(style(~marginBottom=8.->dp, ()))>
          <Text> {React.string(show##item##name)} </Text>
        </TouchableOpacity>
      }
    />
  </SafeAreaView>;
};
