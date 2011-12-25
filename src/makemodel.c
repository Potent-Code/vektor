/* convert a COLLADA dae to Vektor model
 * by Ryan Lucchese
 * December 21 2010 */

#include "makemodel.h"

void load_geometries(model mdl, xmlNodePtr cur, xmlNsPtr ns);
void load_mesh(model mdl, xmlNodePtr cur, xmlNsPtr ns);
vector load_array(xmlNodePtr cur);

model load_model(char* filename)
{
	xmlDocPtr doc;
	xmlNsPtr ns;
	xmlNodePtr cur;
	model mdl;

	mdl = malloc(sizeof(*mdl));

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
	
	ns = xmlSearchNsByHref(doc, cur, COLLADA_XMLNS);

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

	size = atoi(count);

	v = zero_vector(size);

	data = xmlNodeGetContent(cur);

	point = strtok(data, " ");

	for(i = 0; i < size; i++)
	{
		v->a[i] = atof(point);
		point = strtok(NULL, " ");
	}

	if (i != size)
	{
		fprintf(stderr, "array size mismatch: expected %d, got %d\n", size, i);
	}	

	xmlFree(count);
	xmlFree(data);

	return v;
}

void load_geometries(model mdl, xmlNodePtr cur, xmlNsPtr ns)
{
	while (cur != NULL)
	{
		if ((xmlStrcmp(cur->name, (const xmlChar*)"geometry") == 0) && (cur->ns == ns))
		{
			mdl->name = xmlGetProp(cur, (const xmlChar*)"name");
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
		
		cur = cur->next;
	}

	if (source_name != NULL) xmlFree(source_name);
}

int save_model(model mdl, char* filename)
{
	if (mdl != NULL) {
		if (mdl->vertices != NULL && mdl->normals != NULL && mdl->tcoords != NULL) {
			printf("Saving model %s to %s\n%d vertices\n%d normals\n%d texcoords\n", mdl->name, filename, mdl->vertices->n, mdl->normals->n, mdl->tcoords->n);
		}
		else {
			printf("Didn't load all data in model %s\n", mdl->name);
		}
	}
}

void free_model(model mdl)
{
	if (mdl != NULL)
	{
		if (mdl->name != NULL)
		{
			xmlFree(mdl->name);
		}
		
		if (mdl->vertices != NULL)
		{
			free_vector(mdl->vertices);
		}

		if (mdl->normals != NULL)
		{
			free_vector(mdl->normals);
		}

		if (mdl->tcoords != NULL)
		{
			free_vector(mdl->tcoords);
		}

		free(mdl);
	}
}

int main(int argc, char** argv)
{
	model mdl;

	if(argc < 3)
	{
		printf("Usage: %s in.dae out.vmodel\nConvert COLLADA dae to Vektor model\n", argv[0]);
		return 0;
	}

	mdl = load_model(argv[1]);

	save_model(mdl, argv[2]);

	free_model(mdl);

	return 0;
}

