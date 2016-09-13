/*
 * Generated by asn1c-0.9.26 (http://lionet.info/asn1c)
 * From ASN.1 module "DNDS"
 * 	found in "dnds.asn1"
 * 	`asn1c -fnative-types`
 */

#ifndef	_Context_H_
#define	_Context_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include "Topology.h"
#include <PrintableString.h>
#include <OCTET_STRING.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Context */
typedef struct Context {
	unsigned long	*id	/* OPTIONAL */;
	unsigned long	 clientId;
	Topology_t	 topology;
	PrintableString_t	*description	/* OPTIONAL */;
	OCTET_STRING_t	 network;
	OCTET_STRING_t	 netmask;
	PrintableString_t	*serverCert	/* OPTIONAL */;
	PrintableString_t	*serverPrivkey	/* OPTIONAL */;
	PrintableString_t	*trustedCert	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Context_t;

/* Implementation */
/* extern asn_TYPE_descriptor_t asn_DEF_id_2;	// (Use -fall-defs-global to expose) */
/* extern asn_TYPE_descriptor_t asn_DEF_clientId_3;	// (Use -fall-defs-global to expose) */
extern asn_TYPE_descriptor_t asn_DEF_Context;

#ifdef __cplusplus
}
#endif

#endif	/* _Context_H_ */
#include <asn_internal.h>