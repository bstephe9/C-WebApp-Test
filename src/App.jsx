import React, { useEffect } from "react";

function App() {
  useEffect(() => {
    // Dynamically load the SDL2 WebAssembly application
    const script = document.createElement("script");
    script.src = `${import.meta.env.BASE_URL}test.js`; // Path to the compiled JavaScript glue code
    script.async = true;

    // Append the script to the document
    document.body.appendChild(script);

    return () => {
      // Cleanup the script on component unmount
      document.body.removeChild(script);
    };
  }, []);

  return (
    <div>
      <h1>Vite + React + SDL2 Example</h1>
      {/* Placeholder for SDL2 rendering */}
      <div
        id="sdl2-container"
        style={{
          width: "800px",
          height: "600px",
          border: "1px solid black",
        }}
      >
        <canvas id="canvas" width="800" height="600"></canvas>
      </div>
    </div>
  );
}

export default App;
