module PlayerControl = {
  [@react.component]
  let make = (~children, ~onClick) => {
    <button className="text-lg text-gray-800" onClick> children </button>;
  };
};

module SmallPlayerControl = {
  [@react.component]
  let make = (~children, ~onClick, ~isActive) => {
    <button
      className={Css.merge([
        "text-sm rounded px-2 py-1 focus:outline-none",
        isActive ? "bg-blue-500 text-white" : "bg-gray-300 text-gray-600",
      ])}
      onClick>
      children
    </button>;
  };
};
