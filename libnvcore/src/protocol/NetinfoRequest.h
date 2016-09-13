/*
 * Generated by asn1c-0.9.26 (http://lionet.info/asn1c)
 * From ASN.1 module "DNDS"
 * 	found in "dnds.asn1"
 * 	`asn1c -fnative-types`
 */

#ifndef	_NetinfoRequest_H_
#define	_NetinfoRequest_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OCTET_STRING.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* NetinfoRequest */
typedef struct NetinfoRequest {
	OCTET_STRING_t	 ipLocal;
	OCTET_STRING_t	 macAddr;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NetinfoRequest_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NetinfoRequest;

#ifdef __cplusplus
}
#endif

#endif	/* _NetinfoRequest_H_ */
#include <asn_internal.h>