#!/bin/bash

# 📌 Script pour ajouter une nouvelle version au CHANGELOG.md
# Utilise Keep a Changelog + SemVer

CHANGELOG_FILE="CHANGELOG.md"

echo "📝 Entrez la nouvelle version (ex: 0.1.1) :"
read VERSION

TODAY=$(date +%F)

# Vérifie si le fichier existe
if [ ! -f "$CHANGELOG_FILE" ]; then
    echo "❌ Le fichier $CHANGELOG_FILE n'existe pas."
    exit 1
fi

# Crée un bloc de version vide à remplir
NEW_ENTRY="## [$VERSION] - $TODAY

### Added
- 

### Changed
- 

### Removed
- 

"

# Insère le nouveau bloc avant [Unreleased]
awk -v new_entry="$NEW_ENTRY" '
BEGIN { inserted=0 }
/## \[Unreleased\]/ && !inserted {
    print $0 "\n" new_entry
    inserted=1
    next
}
{ print }
' "$CHANGELOG_FILE" > "$CHANGELOG_FILE.tmp" && mv "$CHANGELOG_FILE.tmp" "$CHANGELOG_FILE"

echo "✅ Bloc version $VERSION ajouté dans $CHANGELOG_FILE."
