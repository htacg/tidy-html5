var tidy_html5 = function tidy_html5(text, config) {
  FS.writeFile("input.html", text);
  var cmdlineOptions = [];
  if (config) for (var i in config) cmdlineOptions.push("--"+i, config[i]);
  cmdlineOptions.push("-m", "input.html");
  Module.callMain(cmdlineOptions);
  return FS.readFile("input.html", {encoding:"utf8"});
}

var Module = {
  noInitialRun : true,
  noExitRuntime : true
}
