open ReactNavigation;

module M = {
  type params = {uri: string};
};

module RootStack = Stack.Make(M);
