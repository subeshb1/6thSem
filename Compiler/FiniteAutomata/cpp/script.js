let squarer;

function loadWebAssembly(fileName) {
  return fetch(fileName)
    .then(response => response.arrayBuffer())
    .then(bits => WebAssembly.compile(bits))
    .then(module => {
      return new WebAssembly.instantiate(module);
    });
}
console.log("object");
loadWebAssembly("index.wasm").then(instance => {
  squarer = instance.exports;
  console.log("Finished compiling! Ready when you are...");
});
