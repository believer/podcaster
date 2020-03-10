open ReactNavigation;

module RootNavigator = {
  open Navigators;

  [@react.component]
  let make = () => {
    <RootStack.Navigator initialRouteName="Home" headerMode=`none>
      <RootStack.Screen name="Home" component=Home.make />
      <RootStack.Screen name="Player" component=PlayerScreen.make />
    </RootStack.Navigator>;
  };
};

module AppRoot = {
  [@react.component]
  let make = () => {
    <Native.NavigationContainer>
      <RootNavigator />
    </Native.NavigationContainer>;
  };
};

[@react.component]
let make = () => {
  <ApolloHooks.Provider client=GraphQLClient.client>
    <Player.Provider> <AppRoot /> </Player.Provider>
  </ApolloHooks.Provider>;
};

let default = make;
