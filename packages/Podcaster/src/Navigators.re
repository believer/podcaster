open ReactNavigation;

module M = {
  type params = {id: string};
};

module RootStack = Stack.Make(M);
