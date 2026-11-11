import js from '@eslint/js';
import globals from 'globals';

export default [
  { ignores: ['dist/', 'coverage/', 'node_modules/'] },
  js.configs.recommended,
  {
    files: ['**/*.{js,jsx}'],
    languageOptions: {
      ecmaVersion: 'latest',
      sourceType: 'module',
      parserOptions: { ecmaFeatures: { jsx: true } },
      globals: { ...globals.node, ...globals.browser },
    },
    rules: { 'no-unused-vars': ['error', { argsIgnorePattern: '^_', varsIgnorePattern: '^[A-Z]' }] },
  },
  {
    // Subject rule: no `this` on the client side and in the pure game logic.
    files: ['src/client/**', 'src/shared/**'],
    rules: {
      'no-restricted-syntax': ['error', { selector: 'ThisExpression', message: '`this` is forbidden on the client.' }],
    },
  },
  { files: ['tests/**'], languageOptions: { globals: globals.vitest } },
];
