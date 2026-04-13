#!/bin/bash

echo "Generating class diagrams with clang-uml..."
clang-uml -g mermaid

if [ $? -ne 0 ]; then
  echo "Error: clang-uml failed to generate the diagrams."
  exit 1
fi

echo "Writing DOCS.md..."

# Create or overwrite DOCS.md
echo "# Documentation" > DOCS.md
echo "" >> DOCS.md
echo "## Diagramme de classes" >> DOCS.md
echo "" >> DOCS.md
echo '```mermaid' >> DOCS.md
cat diagrams/chess_classes.mmd >> DOCS.md
echo '```' >> DOCS.md

echo "" >> DOCS.md
echo "Success! Docs generated in DOCS.md"
