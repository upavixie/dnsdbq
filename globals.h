/*
 * Copyright (c) 2014-2020 by Farsight Security, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED 1

#include <stdarg.h>
#include "defs.h"
#include "deduper.h"
#include "sort.h"
#include "time.h"

#ifdef MAIN_PROGRAM
#define EXTERN
#define INIT(...) = __VA_ARGS__
#else
#define EXTERN extern
#define INIT(...)
#endif

#ifndef MAIN_PROGRAM
extern const struct verb verbs[];
#endif

EXTERN	const char id_swclient[]	INIT("dnsdbq");
EXTERN	const char id_version[]		INIT("2.6.5");
EXTERN	const char *program_name	INIT(NULL);
EXTERN	const char path_sort[]		INIT("/usr/bin/sort");
EXTERN	const char json_header[]	INIT("Accept: application/json");
EXTERN	const char jsonl_header[]	INIT("Accept: application/x-ndjson");
EXTERN	const char env_time_fmt[]	INIT("DNSDBQ_TIME_FORMAT");
EXTERN	const char env_config_file[]	INIT("DNSDBQ_CONFIG_FILE");
EXTERN	const char env_timeout[]	INIT("DNSDBQ_TIMEOUT");
EXTERN	const char status_noerror[]	INIT("NOERROR");
EXTERN	const char status_error[]	INIT("ERROR");
EXTERN	const char *asinfo_domain	INIT("asn.routeviews.org");
EXTERN	struct qparam qparam_empty INIT({ .query_limit = -1L,
			.explicit_output_limit = -1L, .output_limit = -1L });
EXTERN	char *cookie_file		INIT(NULL);
EXTERN	char *config_file		INIT(NULL);
EXTERN	verb_ct pverb			INIT(NULL);
EXTERN	pdns_system_ct psys		INIT(NULL);
EXTERN	int debug_level			INIT(0);
EXTERN	bool asinfo_lookup		INIT(false);
EXTERN	bool donotverify		INIT(false);
EXTERN	bool quiet			INIT(false);
EXTERN	bool iso8601			INIT(false);
EXTERN	bool multiple			INIT(false);
EXTERN	bool psys_specified		INIT(false);
EXTERN	int transforms			INIT(0);
EXTERN	long max_count			INIT(0L);
EXTERN	sort_e sorting			INIT(no_sort);
EXTERN	batch_e batching		INIT(batch_none);
EXTERN	present_e presentation		INIT(pres_none);
EXTERN	char *presentation_name		INIT(NULL);
EXTERN	presenter_ct presenter		INIT(NULL);
EXTERN	struct timeval startup_time	INIT({});
EXTERN	int exit_code			INIT(0);
EXTERN	long curl_ipresolve		INIT(CURL_IPRESOLVE_WHATEVER);
EXTERN	long curl_timeout		INIT(0L);
EXTERN	deduper_t minimal_deduper	INIT(NULL);

/* deduplication table size. trades memory efficiency (an array of this many
 * pointers will be allocated under '-p minimal' conditions) against run time
 * efficiency (the string's hash will be modulo this size).
 */
EXTERN	const size_t minimal_modulus	INIT(10000);

#undef INIT
#undef EXTERN

__attribute__((noreturn)) void my_exit(int);
__attribute__((noreturn)) void my_panic(bool, const char *);

/* my_logf -- annotate to stderr with program name and current time */
static inline void
my_logf(const char *fmtstr, ...) {
	va_list ap;

	va_start(ap, fmtstr);
	fprintf(stderr, "%s [%s]: ", program_name,
		time_str((u_long)time(NULL), false));
	vfprintf(stderr, fmtstr, ap);
	putc('\n', stderr);
}

#endif /*GLOBALS_H_INCLUDED*/
