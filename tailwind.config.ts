/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
    "./src/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        'text': '#F0EBD8',
        'background': '#0D1321',
        'primary': '#748CAB',
        'secondary': '#1D2D44',
        'accent': '#b12af6',
      },
      transitionProperty: {
        'width': 'width'
    },
    },
  },
  plugins: [import('tailwindcss-font-inter')],
}

