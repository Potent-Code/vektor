/* convert a COLLADA dae to Vektor model
 * by Ryan Lucchese
 * December 24 2011 */

#include "makemodel.h"

void load_model_images(model mdl, xmlNodePtr cur, xmlNsPtr ns);
void load_geometries(model mdl, xmlNodePtr cur, xmlNsPtr ns);
void load_mesh(model mdl, xmlNodePtr cur, xmlNsPtr ns);
vector load_array(xmlNodePtr cur);
uvector load_int_array(xmlNodePtr cur, unsigned int size);

char* model_file;

model load_dae(char* filename)
{
	xmlDocPtr doc;
	xmlNsPtr ns;
	xmlNodePtr cur;
	model mdl;

	mdl = calloc(1, sizeof(*mdl));

	mdl->vertices = NULL;
	mdl->normals = NULL;
	mdl->tcoords = NULL;

	doc = xmlParseFile(filename);

	if (doc == NULL)
	{
		fprintf(stderr, "Error parsing xml file\n");
		return NULL;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL)
	{
		fprintf(stderr, "Could not get root element\n");
		xmlFreeDoc(doc);
		return NULL;
	}
	
	ns = xmlSearchNsByHref(doc, cur, (const xmlChar*)COLLADA_XMLNS);

	if (ns == NULL)
	{
		fprintf(stderr, "XML Namespace mismatch, expecting %s\n", COLLADA_XMLNS);
		xmlFreeDoc(doc);
		return NULL;
	}

	// step into root node
	cur = cur->xmlChildrenNode;

	// find library_geometries root node
	while (cur != NULL)
	{
		//printf("Processing node %s\n", cur->name);
		if ((xmlStrcmp(cur->name, (const xmlChar*)"library_geometries") == 0) && (cur->ns == ns))
		{
			load_geometries(mdl, cur->xmlChildrenNode, ns);
		}

		if ((xmlStrcmp(cur->name, (const xmlChar*)"library_images") == 0) && (cur->ns == ns))
		{
			load_model_images(mdl, cur->xmlChildrenNode, ns);
		}

		cur = cur->next;
	}

	xmlCleanupParser();
	xmlFreeDoc(doc);

	return mdl;
}

vector load_array(xmlNodePtr cur)
{
	xmlChar* count = xmlGetProp(cur, (const xmlChar*)"count");
	xmlChar* data;
	xmlChar* point;
	vector v;
	int size;
	int i;

	if (count == NULL)
	{
		fprintf(stderr, "couldn't get array size\n");
		return NULL;
	}

	size = atoi((const char*)count);

	v = zero_vector(size);

	data = xmlNodeGetContent(cur);

	point = (xmlChar*)strtok((char*)data, " ");

	for (i = 0; i < size; i++)
	{
		v->a[i] = atof((char*)point);
		point = (xmlChar*)strtok(NULL, " ");
	}

	xmlFree(count);
	xmlFree(data);

	return v;
}

uvector load_int_array(xmlNodePtr cur, unsigned int size)
{
	xmlChar* data = xmlNodeGetContent(cur);
	xmlChar* point;
	uvector uv;
	unsigned int i;

	uv = zero_uvector(size);

	point = (xmlChar*)strtok((char*)data, " ");

	for (i = 0; i < size; i++)
	{
		uv->a[i] = atoi((char*)point);
		point = (xmlChar*)strtok(NULL, " ");
	}

	xmlFree(data);

	return uv;
}

void load_model_images(model mdl, xmlNodePtr cur, xmlNsPtr ns)
{
	xmlChar* filename = NULL;
	xmlNodePtr tmp;
	char texture_file[256];
	char texture_png[256];
	pid_t pid;

	while (cur != NULL)
	{
		if ((xmlStrcmp(cur->name, (const xmlChar*)"image") == 0) && (cur->ns == ns))
		{
			tmp = cur;
			cur = cur->xmlChildrenNode;
			while (cur != NULL)
			{
				if ((xmlStrcmp(cur->name, (const xmlChar*)"init_from") == 0) && (cur->ns == ns))
				{
					filename = xmlNodeGetContent(cur);
					if (filename != NULL)
					{
						filename[strlen((char*)filename) - 4] = 0; // remove file extension

						snprintf(texture_file, 255, "%s/%s.texture", model_file, filename);
						snprintf(texture_png, 255, "%s/../%s.png", model_file, filename);
						xmlFree(filename);

						strncpy(mdl->texture_file, texture_file, 255);

						pid = fork();

						if (pid == 0)
						{ // make texture with child process
							execl("/usr/local/bin/maketexture", "maketexture", texture_png, texture_file, NULL);
						} else {
							waitpid(pid, 0, 0);
						}
					}
					break;
				}
				cur = cur->next;
			}
			cur = tmp->next;
			continue;
		}
		cur = cur->next;
	}
}

void load_geometries(model mdl, xmlNodePtr cur, xmlNsPtr ns)
{
	xmlChar* model_name = NULL;

	while (cur != NULL)
	{
		if ((xmlStrcmp(cur->name, (const xmlChar*)"geometry") == 0) && (cur->ns == ns))
		{
			model_name = xmlGetProp(cur, (const xmlChar*)"name");
			strncpy(mdl->name, (const char*)model_name, strlen((const char*)model_name) + 1);
			xmlFree(model_name);
			cur = cur->xmlChildrenNode;
			continue;
		}

		if ((xmlStrcmp(cur->name, (const xmlChar*)"mesh") == 0) && (cur->ns == ns))
		{
			load_mesh(mdl, cur->xmlChildrenNode, ns);
			return; // only load 1 mesh for now
		}
		cur = cur->next;
	}
}

void load_mesh(model mdl, xmlNodePtr cur, xmlNsPtr ns)
{
	xmlNodePtr tmp;
	xmlChar* source_name = NULL;
	xmlChar* count = NULL;
	xmlChar* semantic = NULL;
	xmlChar* offset = NULL;
	unsigned int i = 0;
	unsigned int polys = 0;
	unsigned int polylist_size = 0;

	while (cur != NULL)
	{
		if (source_name != NULL) 
		{
			xmlFree(source_name);
			source_name = NULL;
		}

		if ((xmlStrcmp(cur->name, (const xmlChar*)"source") == 0) && (cur->ns == ns))
		{
			source_name = xmlGetProp(cur, (const xmlChar*)"name");

			// find vertex array
			if (xmlStrcmp(source_name, (const xmlChar*)"position") == 0)
			{
				tmp = cur;
				cur = cur->xmlChildrenNode;

				while (cur != NULL)
				{
					if ((xmlStrcmp(cur->name, (const xmlChar*)"float_array") == 0) && (cur->ns == ns))
					{
						mdl->vertices = load_array(cur);
						cur = tmp->next;
						break;
					}

					cur = cur->next;
				}

				cur = tmp->next;
				continue;
			}

			// find normals array
			if (xmlStrcmp(source_name, (const xmlChar*)"normal") == 0)
			{
				tmp = cur;
				cur = cur->xmlChildrenNode;

				while (cur != NULL)
				{
					if ((xmlStrcmp(cur->name, (const xmlChar*)"float_array") == 0) && (cur->ns == ns))
					{
						mdl->normals = load_array(cur);
						cur = tmp->next;
						break;
					}

					cur = cur->next;
				}

				cur = tmp->next;
				continue;
			}

			// find texture coordinates array
			if (xmlStrcmp(source_name, (const xmlChar*)"map1") == 0)
			{
				tmp = cur;
				cur = cur->xmlChildrenNode;

				while (cur != NULL)
				{
					if ((xmlStrcmp(cur->name, (const xmlChar*)"float_array") == 0) && (cur->ns == ns))
					{
						mdl->tcoords = load_array(cur);
						cur = tmp->next;
						break;
					}

					cur = cur->next;
				}

				cur = tmp->next;
				continue;
			}
		}

		// get polygon list
		if ((xmlStrcmp(cur->name, (const xmlChar*)"polylist") == 0) && (cur->ns == ns))
		{
			count = xmlGetProp(cur, (const xmlChar*)"count");
			polys = atoi((const char*)count);
			xmlFree(count);

			tmp = cur;
			cur = cur->xmlChildrenNode;

			while (cur != NULL)
			{
				if ((xmlStrcmp(cur->name, (const xmlChar*)"input") == 0) && (cur->ns == ns))
				{
					semantic = xmlGetProp(cur, (const xmlChar*)"semantic");
					if (xmlStrcmp(semantic, (const xmlChar*)"VERTEX") == 0)
					{
						offset = xmlGetProp(cur, (const xmlChar*)"offset");
						mdl->vertices->offset = atoi((const char*)offset);
						xmlFree(offset);
					}
					else if (xmlStrcmp(semantic, (const xmlChar*)"NORMAL") == 0)
					{
						offset = xmlGetProp(cur, (const xmlChar*)"offset");
						mdl->normals->offset = atoi((const char*)offset);
						xmlFree(offset);
					}
					else if(xmlStrcmp(semantic, (const xmlChar*)"TEXCOORD") == 0)
					{
						offset = xmlGetProp(cur, (const xmlChar*)"offset");
						mdl->tcoords->offset = atoi((const char*)offset);
						xmlFree(offset);
					}
					xmlFree(semantic);
				}
				else if ((xmlStrcmp(cur->name, (const xmlChar*)"vcount") == 0) && (cur->ns == ns))
				{
					mdl->vcount = load_int_array(cur, polys);
				}
				else if ((xmlStrcmp(cur->name, (const xmlChar*)"p") == 0) && (cur->ns == ns))
				{
					for (i = 0; i < mdl->vcount->n; i++)
					{
						polylist_size += mdl->vcount->a[i] * 3;
					}

					mdl->polylist = load_int_array(cur, polylist_size);
				}

				cur = cur->next;
			}

			cur = tmp->next;
			continue;
		}
		
		cur = cur->next;
	}

	if (source_name != NULL) xmlFree(source_name);
}

int main(int argc, char** argv)
{
	model mdl;
	const mode_t mode_dir = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH; // 0755
	//const mode_t mode_files = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // 0644

	if(argc < 3)
	{
		printf("Usage: %s in.dae out.vmodel\nConvert COLLADA dae to Vektor model\n", argv[0]);
		return 0;
	}

	model_file = argv[2];

	if (mkdir(model_file, mode_dir) != 0)
	{
		if (errno != EEXIST)
		{
			perror("Couldn't create vmodel");
			return 1;
		}
	}

	mdl = load_dae(argv[1]);

	if (mdl == NULL)
	{
		return 1;
	}

	if (chdir(model_file) != 0)
	{
		perror("Couldn't change directory");
		return 1;
	}

	if (mkdir((char*)mdl->name, mode_dir) != 0)
	{
		if (errno != EEXIST)
		{
			perror("Error creating directory");
			return 1;
		}
	}

	model_save(mdl, model_file);

	model_free(mdl);

	return 0;
}

