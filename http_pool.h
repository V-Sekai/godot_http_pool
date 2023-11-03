/**************************************************************************/
/*  summator.h                                                            */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef HTTP_POOL_H
#define HTTP_POOL_H

#include "core/io/file_access.h"
#include "core/io/http_client.h"
#include "core/io/stream_peer_tcp.h"
#include "core/io/stream_peer_tls.h"
#include "core/object/ref_counted.h"
#include "core/os/os.h"
#include "scene/main/node.h"

class Future : public Object {
	GDCLASS(Future, Object);

protected:
	static void _bind_methods() {
		ADD_SIGNAL(MethodInfo("completed", PropertyInfo(Variant::OBJECT, "http", PROPERTY_HINT_RESOURCE_TYPE, "HTTPClient")));
	}
};

class HTTPState : public RefCounted {
	GDCLASS(HTTPState, RefCounted);

public:
	static const int YIELD_PERIOD_MS = 50;

	String out_path;

	Ref<HTTPClient> http;
	bool busy = false;
	bool cancelled = false;
	bool terminated = false;

	bool sent_request = false;
	int status = 0;
	int connect_err = OK;

	int response_code = 0;
	PackedByteArray response_body;
	Dictionary response_headers;
	Ref<FileAccess> file;
	int bytes = 0;
	int total_bytes = 0;

protected:
	static void _bind_methods();

public:
	void _init();
	void set_output_path(String p_out_path);
	void cancel();
	void term();
	void http_tick();
	Ref<HTTPClient> connect_http(String p_hostname, int p_port, bool p_use_ssl);
	Variant wait_for_request();
	void release();
};

class HTTPPool : public Node {
	GDCLASS(HTTPPool, Node);

private:
	int next_request = 0;
	Dictionary pending_requests; // int -> Future

	Array http_client_pool;
	int total_http_clients = 5;

protected:
	static void _bind_methods();
	void _notification(int p_what);

public:
	void set_total_clients(int p_total) {
		total_http_clients = p_total;
	}

	int get_total_clients() const {
		return total_http_clients;
	}
	Ref<HTTPClient> _acquire_client();
	void _release_client(Ref<HTTPClient> p_http);
	Ref<HTTPState> new_http_state();
};

void HTTPState::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_output_path", "out_path"), &HTTPState::set_output_path);
	ClassDB::bind_method(D_METHOD("cancel"), &HTTPState::cancel);
	ClassDB::bind_method(D_METHOD("term"), &HTTPState::term);
	ClassDB::bind_method(D_METHOD("http_tick"), &HTTPState::http_tick);
	ClassDB::bind_method(D_METHOD("connect_http", "hostname", "port", "use_ssl"), &HTTPState::connect_http);
	ClassDB::bind_method(D_METHOD("wait_for_request"), &HTTPState::wait_for_request);
	ClassDB::bind_method(D_METHOD("release"), &HTTPState::release);
}

void HTTPState::set_output_path(String p_out_path) {
	// Set output path code here.
}

void HTTPState::cancel() {
	// Cancel code here.
}

void HTTPState::term() {
	// Terminate code here.
}

void HTTPState::http_tick() {
	// HTTP tick code here.
}

Ref<HTTPClient> HTTPState::connect_http(String p_hostname, int p_port, bool p_use_ssl) {
	// Connect to HTTP code here.
	return Ref<HTTPClient>();
}

Variant HTTPState::wait_for_request() {
	// Wait for request code here.
	return Variant();
}

void HTTPState::release() {
	// Release code here.
}

void HTTPPool::_bind_methods() {
	ADD_SIGNAL(MethodInfo("http_tick"));
	ClassDB::bind_method(D_METHOD("set_total_clients", "out_path"), &HTTPPool::set_total_clients);
	ClassDB::bind_method(D_METHOD("get_total_clients"), &HTTPPool::get_total_clients);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "total_http_clients"), "set_total_clients", "get_total_clients");
	ClassDB::bind_method(D_METHOD("_acquire_client"), &HTTPPool::_acquire_client);
	ClassDB::bind_method(D_METHOD("_release_client", "http"), &HTTPPool::_release_client);
	ClassDB::bind_method(D_METHOD("new_http_state"), &HTTPPool::new_http_state);
}

Ref<HTTPClient> HTTPPool::_acquire_client() {
	// Acquire client code here.
	return Ref<HTTPClient>();
}

void HTTPPool::_release_client(Ref<HTTPClient> http) {
	// Release client code here.
}

Ref<HTTPState> HTTPPool::new_http_state() {
	// New HTTP state code here.
	return Ref<HTTPState>();
}

void HTTPPool::_notification(int p_what) {
	switch (p_what) {
		case Node::NOTIFICATION_INTERNAL_PROCESS: {
		} break;
		case Node::NOTIFICATION_POSTINITIALIZE: {
		} break;
	}
}

#endif // HTTP_POOL_H
