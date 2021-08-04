/* SPDX-FileCopyrightText: 2021 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */

#include "test_common.h"

// clang-format off
const struct wrp_string list[3] = {
    { .s = "Partner 1", .len = 9 },
    { .s = "Partner 2", .len = 9 },
    { .s = "Example",   .len = 7 },
};

const struct wrp_nvp meta[3] = {
    { .name.s = "n1", .name.len = 2, .value.s = "v1",  .value.len = 2 },
};

const struct test_vector test = {
    .wrp_from_msgpack_rv = WRPE_OK,
    .wrp_to_msgpack_rv   = WRPE_OK,
    .wrp_to_string_rv    = WRPE_OK,

    .in.msg_type                = WRP_MSG_TYPE__REQ,
    .in.u.req.trans_id.s        = "c07ee5e1-70be-444c-a156-097c767ad8aa",
    .in.u.req.trans_id.len      = 36,
    .in.u.req.source.s          = "source-address",
    .in.u.req.source.len        = 14,
    .in.u.req.dest.s            = "dest-address",
    .in.u.req.dest.len          = 12,
    .in.u.req.partner_ids.count = 3,
    .in.u.req.partner_ids.list  = (struct wrp_string*) list,
    .in.u.req.content_type.s    = "application/json",
    .in.u.req.content_type.len  = 16,
    .in.u.req.payload.data      = (const uint8_t*) "123",
    .in.u.req.payload.len       = 3,
    .in.u.req.accept.s          = "json",
    .in.u.req.accept.len        = 4,
    .in.u.req.metadata.count    = 1,
    .in.u.req.metadata.list     = (struct wrp_nvp*) meta,

    .string = "wrp_req_msg {\n"
              "    .trans_id      = 'c07ee5e1-70be-444c-a156-097c767ad8aa'\n"
              "    .source        = 'source-address'\n"
              "    .dest          = 'dest-address'\n"
              "    .partner_ids   = 'Partner 1, Partner 2, Example'\n"
              "    .content_type  = 'application/json'\n"
              "    .accept        = 'json'\n"
              "    .payload (len) = 3\n"
              "    .metadata      = {\n"
              "        .n1: 'v1'\n"
              "    }\n"
              "}\n",

    .msgpack_len = 218,
    .msgpack =
        "\x89"  /* 9 name value pairs */
            "\xa8""msg_type"         /* : */ "\x03" // 3
            "\xa6""source"           /* : */ "\xae""source-address"
            "\xa4""dest"             /* : */ "\xac""dest-address"
            "\xab""partner_ids"      /* : */ "\x93" // 3
                                                 "\xa9""Partner 1"
                                                 "\xa9""Partner 2"
                                                 "\xa7""Example"
            "\xa8""metadata"         /* : */ "\x81" // 1
                                                 "\xa2""n1" "\xa2""v1"
            "\xb0""transaction_uuid" /* : */ "\xd9\x24""c07ee5e1-70be-444c-a156-097c767ad8aa"
            "\xac""content_type"     /* : */ "\xb0""application/json"
            "\xa6""accept"           /* : */ "\xa4""json"
            "\xa7""payload"          /* : */ "\xc4""\x03" /* len 3 */
                                             "123"
};
// clang-format on

const char *test_name = __FILE__;