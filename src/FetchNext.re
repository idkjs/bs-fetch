type body;

type bodyInit;

type headers;

type headersInit;

type response;

type request;

type requestInit;

/* external */
type arrayBuffer; /* TypedArray */

type blob; /* FileAPI */

type bufferSource; /* Web IDL, either an arrayBuffer or arrayBufferView */

type formData; /* XMLHttpRequest */

type readableStream; /* Streams */

type urlSearchParams; /* URL */

module Method = {
  type t = string;
  let get = "GET";
  let head = "HEAD";
  let post = "POST";
  let put = "PUT";
  let delete = "DELETE";
  let connect = "CONNECT";
  let options = "OPTIONS";
  let trace = "TRACE";
  let patch = "PATCH";
  let other = (m) => m;
};

module ReferrerPolicy = {
  type t = string;
  let none = "";
  let noReferrer = "no-referrer";
  let noReferrerWhenDowngrade = "no-referrer-when-downgrade";
  let sameOrigin = "same-origin";
  let origin = "origin";
  let strictOrigin = "strict-origin";
  let originWhenCrossOrigin = "origin-when-cross-origin";
  let strictOriginWhenCrossOrigin = "strict-origin-when-cross-origin";
  let unsafeUrl = "unsafe-url";
};

module RequestType = {
  type t = string;
  let none = "";
  let audio = "audio";
  let font = "font";
  let image = "image";
  let script = "script";
  let style = "style";
  let track = "track";
  let video = "video";
};

module RequestDestination = {
  type t = string;
  let none = "";
  let document = "document";
  let embed = "embed";
  let font = "font";
  let image = "image";
  let manifest = "manifest";
  let media = "media";
  let object_ = "object";
  let report = "report";
  let script = "script";
  let serviceWorker = "serviceworker";
  let sharedWorker = "sharedworder";
  let style = "style";
  let worker = "worker";
  let xslt = "xslt";
};

module RequestMode = {
  type t = string;
  let navigate = "navigate";
  let sameOrigin = "same-origin";
  let noCORS = "no-cors";
  let cors = "cors";
};

module RequestCredentials = {
  type t = string;
  let omit = "omit";
  let sameOrigin = "same-origin";
  let include_ = "include";
};

module RequestCache = {
  type t = string;
  let default = "default";
  let noStore = "no-store";
  let reload = "reload";
  let noCache = "no-cache";
  let forceCache = "force-cache";
  let onlyIfCached = "only-if-cached";
};

module RequestRedirect = {
  type t = string;
  let follow = "follow";
  let error = "error";
  let manual = "manual";
};

module HeadersInit = {
  type t = headersInit;
  external make : Js.t({..}) => t = "%identity";
  external makeWithArray : array((string, string)) => t = "%identity";
};

module Headers = {
  type t = headers;
  [@bs.new] external make : t = "Headers";
  [@bs.new] external makeWithInit : headersInit => t = "Headers";
  [@bs.send.pipe : t] external append : string => string = "append";
  [@bs.send.pipe : t] external delete : string = "delete" /* very experimental */; /* entries */
  [@bs.send.pipe : t] [@bs.return {null_to_opt: null_to_opt}]
  external get : string => option(string) = "get";
  [@bs.send.pipe : t] external has : string => bool = "has" /* very experimental */; /* keys */
  [@bs.send.pipe : t] external set : (string, string) => unit = "set" /* very experimental */; /* values */
};

module BodyInit = {
  type t = bodyInit;
  external make : string => t = "%identity";
  external makeWithBlob : blob => t = "%identity";
  external makeWithBufferSource : bufferSource => t = "%identity";
  external makeWithFormData : formData => t = "%identity";
  external makeWithUrlSearchParams : urlSearchParams => t = "%identity";
};

module Body = {
  module Impl = (T: {type t;}) => {
    [@bs.get] external body : T.t => readableStream = "body";
    [@bs.get] external bodyUsed : T.t => bool = "bodyUsed";
    [@bs.send.pipe : T.t] external arrayBuffer : Js.Promise.t(arrayBuffer) = "arrayBuffer";
    [@bs.send.pipe : T.t] external blob : Js.Promise.t(blob) = "blob";
    [@bs.send.pipe : T.t] external formData : Js.Promise.t(formData) = "formData";
    [@bs.send.pipe : T.t] external json : Js.Promise.t(Js.Json.t) = "json";
    [@bs.send.pipe : T.t] external text : Js.Promise.t(string) = "text";
  };
  type t = body;
  include
    Impl(
      {
        type nonrec t = t;
      }
    );
};

module RequestInit = {
  type t = requestInit;
  [@bs.obj]
  external make :
    (
      ~_method: Method.t=?,
      ~headers: headersInit=?,
      ~body: bodyInit=?,
      ~referrer: string=?,
      ~referrerPolicy: ReferrerPolicy.t=?,
      ~mode: RequestMode.t=?,
      ~credentials: RequestCredentials.t=?,
      ~cache: RequestCache.t=?,
      ~redirect: RequestRedirect.t=?,
      ~integrity: string=?,
      ~keepalive: bool=?,
      unit
    ) =>
    requestInit =
    "";
};

module Request = {
  type t = request;
  include
    Body.Impl(
      {
        type nonrec t = t;
      }
    );
  [@bs.new] external make : string => t = "Request";
  [@bs.new] external makeWithInit : (string, requestInit) => t = "Request";
  [@bs.new] external makeWithRequest : t => t = "Request";
  [@bs.new] external makeWithRequestInit : (t, requestInit) => t = "Request";
  [@bs.get] external method_ : t => string = "method";
  /*let method_: t -> requestMethod = fun self -> decodeRequestMethod (method_ self)*/
  [@bs.get] external url : t => string = "url";
  [@bs.get] external headers : t => headers = "headers";
  [@bs.get] external type_ : t => RequestType.t = "type";
  [@bs.get] external destination : t => RequestDestination.t = "destination";
  [@bs.get] external referrer : t => string = "referrer";
  [@bs.get] external referrerPolicy : t => ReferrerPolicy.t = "referrerPolicy";
  [@bs.get] external mode : t => RequestMode.t = "mode";
  [@bs.get] external credentials : t => RequestCredentials.t = "credentials";
  [@bs.get] external cache : t => RequestCache.t = "cache";
  [@bs.get] external redirect : t => RequestRedirect.t = "redirect";
  [@bs.get] external integrity : t => string = "integrity";
  [@bs.get] external keepalive : t => bool = "keepalive";
};

module Response = {
  type t = response;
  include
    Body.Impl(
      {
        type nonrec t = t;
      }
    );
  [@bs.val] external error : unit => t = "error";
  [@bs.val] external redirect : string => t = "redirect";
  [@bs.val] external redirectWithStatus : (string, int /* enum-ish */) => t = "redirect";
  [@bs.get] external headers : t => headers = "headers";
  [@bs.get] external ok : t => bool = "ok";
  [@bs.get] external redirected : t => bool = "redirected";
  [@bs.get] external status : t => int = "status";
  [@bs.get] external statusText : t => string = "statusText";
  [@bs.get] external _type : t => string = "type";
  [@bs.get] external url : t => string = "url";
  [@bs.send.pipe : t] external clone : t = "clone";
};

[@bs.val] external fetch : string => Js.Promise.t(response) = "fetch";

[@bs.val] external fetchWithInit : (string, requestInit) => Js.Promise.t(response) = "fetch";

[@bs.val] external fetchWithRequest : request => Js.Promise.t(response) = "fetch";

[@bs.val]
external fetchWithRequestInit : (request, requestInit) => Js.Promise.t(response) = "fetch";
