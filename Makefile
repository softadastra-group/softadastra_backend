VERSION ?= v0.1.0
BRANCH_DEV = dev
BRANCH_MAIN = main

.PHONY: help release commit push merge tag test

help:
	@echo "Available commands:"
	@echo "  make commit               - Add and commit all files (on dev branch)"
	@echo "  make push                 - Push the dev branch"
	@echo "  make merge                - Merge dev into main"
	@echo "  make tag VERSION=vX.Y.Z  - Create a Git tag (default: $(VERSION))"
	@echo "  make release VERSION=vX.Y.Z - Full release: commit + push + merge + tag"
	@echo "  make test                 - Compile and run tests"

commit:
	git checkout $(BRANCH_DEV)
	@if [ -n "$$(git status --porcelain)" ]; then \
		echo "📝 Committing changes..."; \
		git add .; \
		git commit -m "🚀 Update: automated commit via Makefile"; \
	else \
		echo "✅ Nothing to commit."; \
	fi

push:
	git push origin $(BRANCH_DEV)

merge:
	git checkout $(BRANCH_MAIN)
	git merge --no-ff --no-edit $(BRANCH_DEV)
	git push origin $(BRANCH_MAIN)

tag:
	git tag $(VERSION)
	git push origin $(VERSION)

release:
	make commit
	make push
	make merge
	make tag VERSION=$(VERSION)

test:
	cd build && ctest --output-on-failure

changelog:
	bash scripts/update_changelog.sh

