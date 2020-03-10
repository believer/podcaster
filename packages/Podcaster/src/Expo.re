/*module Audio = {*/
/*type t;*/
/*[@bs.new] [@bs.module "expo-av"] [@bs.scope "Audio"]*/
/*external make: unit => t = "Sound";*/
/*type loadOptions = {uri: string};*/
/*[@bs.send]*/
/*external load: (t, loadOptions) => Js.Promise.t(unit) = "loadAsync";*/
/*type createStatus('a) = {*/
/*sound: t,*/
/*status: Js.t('a),*/
/*};*/
/*type initialOptions = {shouldPlay: bool};*/
/*[@bs.module "expo-av"] [@bs.scope ("Audio", "Sound")]*/
/*external create:*/
/*(loadOptions, option(initialOptions), Js.t('a) => unit) =>*/
/*Js.Promise.t(createStatus('a)) =*/
/*"createAsync";*/
/*module Control = {*/
/*[@bs.send] external play: t => Js.Promise.t(unit) = "playAsync";*/
/*[@bs.send] external pause: t => Js.Promise.t(unit) = "pauseAsync";*/
/*};*/
/*[@bs.send]*/
/*external getStatus: t => Js.Promise.t(Js.t('a)) = "getStatusAsync";*/
/*[@bs.send]*/
/*external setVolume: (t, float) => Js.Promise.t(unit) = "setVolumeAsync";*/
/*[@bs.send]*/
/*external setPosition: (t, float) => Js.Promise.t(unit) = "setPositionAsync";*/
/*module PitchCorrection = {*/
/*type t =*/
/*| High*/
/*| Medium*/
/*| Low;*/
/*let make =*/
/*fun*/
/*| High => "High"*/
/*| Medium => "Medium"*/
/*| Low => "Low";*/
/*};*/
/*[@bs.send]*/
/*external setPlaybackRate: (t, float, bool) => Js.Promise.t(unit) =*/
/*"setRateAsync";*/
/*};*/
