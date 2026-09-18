# 06-ui-mesh-parser

Это неизменённые фрагменты фактического large-16. Псевдокод оригинала — материал для чтения, не компилируемый C++. Числа слева — номера строк исходного файла.

## `src/ogre_mesh.cpp:106–140`

SHA256 полного файла: `2ea71e275987f63b43881ad193ba4e395a6ad52c81ca496af48375d75c7d41f6`

```text
  106 |         return result;
  107 |     }
  108 | 
  109 |     Chunk read_chunk(std::size_t container_end) {
  110 |         const auto id = read_u16(container_end, "OGRE chunk ID");
  111 |         const auto length = read_u32(container_end, "OGRE chunk length");
  112 |         if (length < 6U) {
  113 |             throw OgreMeshError("OGRE chunk is shorter than its header");
  114 |         }
  115 |         const auto payload_size = static_cast<std::size_t>(length - 6U);
  116 |         if (payload_size > bytes_.size() - position_) {
  117 |             if (container_end == bytes_.size()) {
  118 |                 return Chunk{id, container_end};
  119 |             }
  120 |             throw OgreMeshError("OGRE chunk " + std::to_string(id) + " at " +
  121 |                                 std::to_string(position_ - 6U) + " with length " +
  122 |                                 std::to_string(length) + " exceeds the input");
  123 |         }
  124 |         return Chunk{id, position_ + payload_size};
  125 |     }
  126 | 
  127 |     Chunk read_root_chunk() {
  128 |         const auto id = read_u16(bytes_.size(), "OGRE root chunk ID");
  129 |         const auto length = read_u32(bytes_.size(), "OGRE root chunk length");
  130 |         if (length < 6U) {
  131 |             throw OgreMeshError("OGRE root chunk is shorter than its header");
  132 |         }
  133 |         return Chunk{id, bytes_.size()};
  134 |     }
  135 | 
  136 |     void seek(std::size_t position) {
  137 |         if (position > bytes_.size()) {
  138 |             throw OgreMeshError("OGRE seek exceeds the input");
  139 |         }
  140 |         position_ = position;
```

## `src/ogre_mesh.cpp:324–432`

SHA256 полного файла: `2ea71e275987f63b43881ad193ba4e395a6ad52c81ca496af48375d75c7d41f6`

```text
  324 |     if (texcoord->type != kFloat2Type) {
  325 |         throw OgreMeshError("OGRE primary texture coordinate is not FLOAT2");
  326 |     }
  327 |     const auto* texcoord_buffer = find_buffer(geometry, texcoord->source);
  328 |     if (texcoord_buffer == nullptr) {
  329 |         throw OgreMeshError("OGRE texture-coordinate buffer is absent");
  330 |     }
  331 |     geometry.texcoords.reserve(geometry.vertex_count);
  332 |     for (std::uint32_t index = 0; index < geometry.vertex_count; ++index) {
  333 |         const auto offset = static_cast<std::size_t>(index) * texcoord_buffer->stride +
  334 |                             texcoord->offset;
  335 |         geometry.texcoords.push_back({read_buffer_float(texcoord_buffer->data, offset),
  336 |                                       read_buffer_float(texcoord_buffer->data, offset + 4U)});
  337 |     }
  338 | }
  339 | 
  340 | OgreGeometry parse_geometry(Reader& reader, const Chunk& chunk) {
  341 |     OgreGeometry geometry;
  342 |     geometry.vertex_count = reader.read_u32(chunk.end, "OGRE geometry vertex count");
  343 |     while (reader.can_read(6, chunk.end) &&
  344 |            (reader.peek_u16(chunk.end) == kVertexDeclaration ||
  345 |             reader.peek_u16(chunk.end) == kVertexBuffer)) {
  346 |         const auto child = reader.read_chunk(chunk.end);
  347 |         if (child.id == kVertexDeclaration) {
  348 |             while (reader.can_read(6, child.end) &&
  349 |                    reader.peek_u16(child.end) == kVertexElement) {
  350 |                 const auto element_chunk = reader.read_chunk(child.end);
  351 |                 OgreVertexElement element;
  352 |                 element.source = reader.read_u16(element_chunk.end, "vertex source");
  353 |                 element.type = reader.read_u16(element_chunk.end, "vertex type");
  354 |                 element.semantic = reader.read_u16(element_chunk.end, "vertex semantic");
  355 |                 element.offset = reader.read_u16(element_chunk.end, "vertex offset");
  356 |                 element.index = reader.read_u16(element_chunk.end, "vertex semantic index");
  357 |                 geometry.elements.push_back(element);
  358 |                 reader.seek(element_chunk.end);
  359 |             }
  360 |         } else if (child.id == kVertexBuffer) {
  361 |             OgreVertexBuffer buffer;
  362 |             buffer.binding = reader.read_u16(child.end, "vertex buffer binding");
  363 |             buffer.stride = reader.read_u16(child.end, "vertex buffer stride");
  364 |             const auto data_chunk = reader.read_chunk(child.end);
  365 |             if (data_chunk.id != kVertexBufferData) {
  366 |                 throw OgreMeshError("OGRE vertex buffer has no data chunk");
  367 |             }
  368 |             const auto byte_count = static_cast<std::size_t>(geometry.vertex_count) * buffer.stride;
  369 |             if (buffer.stride != 0 && byte_count / buffer.stride != geometry.vertex_count) {
  370 |                 throw OgreMeshError("OGRE vertex buffer size overflows");
  371 |             }
  372 |             buffer.data = reader.read_bytes(byte_count, data_chunk.end, "vertex buffer data");
  373 |             if (reader.position() != data_chunk.end) {
  374 |                 throw OgreMeshError("OGRE vertex buffer data has an unexpected size");
  375 |             }
  376 |             if (find_buffer(geometry, buffer.binding) != nullptr) {
  377 |                 throw OgreMeshError("Duplicate OGRE vertex buffer binding");
  378 |             }
  379 |             geometry.buffers.push_back(std::move(buffer));
  380 |         }
  381 |         reader.seek(child.end);
  382 |     }
  383 |     finish_geometry(geometry);
  384 |     return geometry;
  385 | }
  386 | 
  387 | OgreSubmesh parse_submesh(Reader& reader, const Chunk& chunk) {
  388 |     OgreSubmesh submesh;
  389 |     submesh.material = reader.read_line(chunk.end, "OGRE material name");
  390 |     submesh.uses_shared_vertices = reader.read_u8(chunk.end, "shared-vertices flag") != 0;
  391 |     const auto index_count = reader.read_u32(chunk.end, "OGRE index count");
  392 |     submesh.indexes_32bit = reader.read_u8(chunk.end, "32-bit-index flag") != 0;
  393 |     const auto index_size = submesh.indexes_32bit ? 4U : 2U;
  394 |     if (index_count > (chunk.end - reader.position()) / index_size) {
  395 |         throw OgreMeshError("OGRE index buffer exceeds its submesh");
  396 |     }
  397 |     submesh.indices.reserve(index_count);
  398 |     for (std::uint32_t index = 0; index < index_count; ++index) {
  399 |         submesh.indices.push_back(submesh.indexes_32bit
  400 |                                       ? reader.read_u32(chunk.end, "32-bit mesh index")
  401 |                                       : reader.read_u16(chunk.end, "16-bit mesh index"));
  402 |     }
  403 |     if (!submesh.uses_shared_vertices) {
  404 |         const auto geometry_chunk = reader.read_chunk(chunk.end);
  405 |         if (geometry_chunk.id != kGeometry) {
  406 |             throw OgreMeshError("OGRE submesh has no local geometry");
  407 |         }
  408 |         submesh.geometry = parse_geometry(reader, geometry_chunk);
  409 |     }
  410 |     while (reader.can_read(6, chunk.end)) {
  411 |         const auto next_id = reader.peek_u16(chunk.end);
  412 |         if (next_id != kSubmeshOperation && next_id != kSubmeshBoneAssignment &&
  413 |             next_id != 0x4200) {
  414 |             break;
  415 |         }
  416 |         const auto child = reader.read_chunk(chunk.end);
  417 |         if (child.id == kSubmeshOperation) {
  418 |             submesh.operation_type = reader.read_u16(child.end, "submesh operation");
  419 |         } else if (child.id == kSubmeshBoneAssignment) {
  420 |             OgreBoneAssignment assignment;
  421 |             assignment.vertex_index =
  422 |                 reader.read_u32(child.end, "submesh bone-assignment vertex index");
  423 |             assignment.bone_index =
  424 |                 reader.read_u16(child.end, "submesh bone-assignment bone index");
  425 |             assignment.weight =
  426 |                 reader.read_float(child.end, "submesh bone-assignment weight");
  427 |             submesh.bone_assignments.push_back(assignment);
  428 |         }
  429 |         reader.seek(child.end);
  430 |     }
  431 |     return submesh;
  432 | }
```

## `src/ogre_mesh.cpp:473–541`

SHA256 полного файла: `2ea71e275987f63b43881ad193ba4e395a6ad52c81ca496af48375d75c7d41f6`

```text
  473 | OgreMesh parse_ogre_mesh(const std::vector<std::uint8_t>& bytes) {
  474 |     Reader reader(bytes);
  475 |     if (reader.read_u16(reader.size(), "OGRE file header") != kHeader) {
  476 |         throw OgreMeshError("OGRE mesh has the wrong header");
  477 |     }
  478 |     OgreMesh mesh;
  479 |     mesh.serializer_version = reader.read_line(reader.size(), "OGRE serializer version");
  480 |     if (mesh.serializer_version != "[MeshSerializer_v1.40]") {
  481 |         throw OgreMeshError("Unsupported OGRE mesh serializer version");
  482 |     }
  483 |     const auto mesh_chunk = reader.read_root_chunk();
  484 |     if (mesh_chunk.id != kMesh) {
  485 |         throw OgreMeshError("OGRE file has no mesh chunk");
  486 |     }
  487 |     mesh.skeletally_animated = reader.read_u8(mesh_chunk.end, "skeletal-animation flag") != 0;
  488 |     while (reader.can_read(6, mesh_chunk.end)) {
  489 |         const auto child = reader.read_chunk(mesh_chunk.end);
  490 |         bool consumed_by_parser = false;
  491 |         switch (child.id) {
  492 |         case kGeometry:
  493 |             if (mesh.shared_geometry.has_value()) {
  494 |                 throw OgreMeshError("OGRE mesh contains duplicate shared geometry");
  495 |             }
  496 |             mesh.shared_geometry = parse_geometry(reader, child);
  497 |             consumed_by_parser = true;
  498 |             break;
  499 |         case kSubmesh:
  500 |             mesh.submeshes.push_back(parse_submesh(reader, child));
  501 |             consumed_by_parser = true;
  502 |             break;
  503 |         case kSkeletonLink:
  504 |             mesh.skeleton_file = reader.read_line(child.end, "OGRE skeleton link");
  505 |             break;
  506 |         case kMeshBoneAssignment: {
  507 |             OgreBoneAssignment assignment;
  508 |             assignment.vertex_index =
  509 |                 reader.read_u32(child.end, "shared bone-assignment vertex index");
  510 |             assignment.bone_index =
  511 |                 reader.read_u16(child.end, "shared bone-assignment bone index");
  512 |             assignment.weight = reader.read_float(child.end, "shared bone-assignment weight");
  513 |             mesh.shared_bone_assignments.push_back(assignment);
  514 |             break;
  515 |         }
  516 |         case kBounds: {
  517 |             OgreMeshBounds bounds;
  518 |             for (auto& coordinate : bounds.minimum) {
  519 |                 coordinate = reader.read_float(child.end, "OGRE minimum bound");
  520 |             }
  521 |             for (auto& coordinate : bounds.maximum) {
  522 |                 coordinate = reader.read_float(child.end, "OGRE maximum bound");
  523 |             }
  524 |             bounds.radius = reader.read_float(child.end, "OGRE bounding radius");
  525 |             mesh.bounds = bounds;
  526 |             break;
  527 |         }
  528 |         default: break;
  529 |         }
  530 |         if (!consumed_by_parser) {
  531 |             reader.seek(child.end);
  532 |         }
  533 |     }
  534 |     if (mesh_chunk.end != reader.size()) {
  535 |         throw OgreMeshError("OGRE mesh has trailing data");
  536 |     }
  537 |     validate_mesh(mesh);
  538 |     return mesh;
  539 | }
  540 | 
  541 | } // namespace torchlight
```

