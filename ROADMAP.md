# 🛣️ Softadastra — Development Roadmap

Softadastra is a modular C++ backend powering a decentralized African ecosystem:  
e-commerce, real-time messaging, payments, P2P storage, business tools, and more.

---

## ✅ Phase 1 — Foundation (✔️ Completed)

| Feature                        | Status  | Notes                                      |
| ------------------------------ | ------- | ------------------------------------------ |
| Modular C++ structure          | ✅ Done | `adastra/`, `softadastra/`, `Crow/include` |
| Core libraries integration     | ✅ Done | JSON, SQLite, MySQL, OpenSSL, Threads      |
| Crow integration (header-only) | ✅ Done | No Boost dependency                        |
| Unit tests (GTest + Catch2)    | ✅ Done | For `core`, `shop`, `search`, `utils`      |
| CI-ready structure             | ✅ Done | Scripts: build, run, test, clean           |

---

## 🚧 Phase 2 — API Modules (In Progress)

| Module      | Endpoint Examples              | Status     |
| ----------- | ------------------------------ | ---------- |
| `commerce`  | `/api/products`, `/api/offers` | 🟡 In Dev  |
| `chat`      | `/api/messages`, WebSocket     | 🔲 Planned |
| `pay`       | `/api/pay`, `/api/wallet`      | 🔲 Planned |
| `box` (P2P) | `/api/upload`, `/api/share`    | 🔲 Planned |
| `map`       | `/api/geo`, `/api/city`        | 🔲 Planned |

✅ Common route: `/api/health` → status check

---

## 🧪 Phase 3 — Testing & Monitoring

| Task                      | Tool / Feature            | Status     |
| ------------------------- | ------------------------- | ---------- |
| API integration tests     | GTest                     | 🟡 Partial |
| Benchmarking & profiling  | `time`, profiling tools   | 🔲 Planned |
| CTest integration         | CMake/CTest               | ✅ Done    |
| Security headers / audits | OpenSSL, Crow middlewares | 🔲 Planned |

---

## 🚀 Phase 4 — Deployment & Ops

| Task                        | Stack / Tool             | Status     |
| --------------------------- | ------------------------ | ---------- |
| Systemd integration         | `softadastra.service`    | ✅ Done    |
| Docker container (optional) | `Dockerfile`, CMake      | 🔲 Planned |
| API production domain       | `api.softadastra.com`    | ✅ Running |
| Monitoring & Logging        | Custom logger, logrotate | 🟡 Partial |

---

## 🎯 Long-Term Goals

- [ ] Add Redis for caching products and categories
- [ ] Add PostgreSQL driver for compatibility
- [ ] Implement Crow middlewares: auth, rate-limit, etc.
- [ ] Generate OpenAPI (Swagger) documentation
- [ ] Add load testing scenarios (k6 or custom C++ tool)

---

## 🔁 Weekly Development Cycle

| Day       | Focus                          |
| --------- | ------------------------------ |
| Monday    | Code cleanup, review, testing  |
| Tuesday   | New features (modules)         |
| Wednesday | Database integration / queries |
| Thursday  | Routes & API consistency       |
| Friday    | Tests, CI scripts, docs        |
| Weekend   | Reserved for refactor / pause  |

---

## 🧑‍💻 Maintainer

**Softadastra Backend Team**  
https://softadastra.com  
Contact: backend@softadastra.com
