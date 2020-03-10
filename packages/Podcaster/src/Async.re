let let_ = (prom, cb) => prom |> Js.Promise.then_(cb);
