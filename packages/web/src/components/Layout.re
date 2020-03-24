type space =
  | Small
  | Large;

type align =
  | Left
  | Center
  | Right;

module Columns = {
  [@react.component]
  let make = (~children, ~space) => {
    let className =
      switch (space) {
      | None => ""
      | Some(Small) => "column-2"
      | Some(Large) => "column-4"
      };

    <div className> children </div>;
  };
};

module Stack = {
  [@react.component]
  let make = (~children, ~space, ~align=None) => {
    let spacing =
      switch (space) {
      | None => ""
      | Some(Small) => "stack-2"
      | Some(Large) => "stack-4"
      };

    let alignment =
      switch (align) {
      | None => ""
      | Some(Left) => "items-start"
      | Some(Center) => "items-center"
      | Some(Right) => "items-end"
      };

    <div
      className=Css.(
        merge([
          spacing,
          alignment,
          align->Belt.Option.isSome ? "flex flex-col" : "",
        ])
      )>
      children
    </div>;
  };
};
