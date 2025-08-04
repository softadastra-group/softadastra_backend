#!/bin/bash

echo "Version ? (ex: 0.1.1)"
read VERSION
TODAY=$(date +%F)

# Crée le bloc version
echo -e "## [$VERSION] - $TODAY\n### Added\n- \n\n### Changed\n- \n\n### Removed\n- \n\n" | cat - CHANGELOG.md > temp && mv temp CHANGELOG.md

# Vide le bloc Unreleased si tu veux le déplacer manuellement ensuite
