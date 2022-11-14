<?php

namespace App\Controllers\API;

use CodeIgniter\RESTful\ResourceController;

class Config extends ResourceController
{
    protected $modelName = 'App\Models\API\Config';

    /**
     * Return an array of resource objects, themselves in array format
     *
     * @return mixed
     */
    public function index()
    {
        $data = $this->model->findAll();
        return $this->respond(['data' => $data]);
    }

    /**
     * Return the properties of a resource object
     *
     * @return mixed
     */
    public function show($id = null)
    {
        $data = $this->model->where('id_config', $id)->first();
        if ($data)
            return $this->respond(['data' => $data]);
        $response = [
            'status' => 404,
            'error'  => true,
            'messages' => [
                'error' => 'Registro no encontrado'
            ]
        ];
        return $this->respondCreated($response, 404);
    }

    /**
     * Return a new resource object, with default properties
     *
     * @return mixed
     */
    public function new()
    {
        //
    }

    /**
     * Create a new resource object, from "posted" parameters
     *
     * @return mixed
     */
    public function create()
    {
        $request = $this->request->getJSON();
        $data = [
            'description'   => $request->description,
            'water_porc'    => $request->water_porc,
            'grain_porc'   => $request->amount_porc
        ];
        $this->model->insert($data);
        $response = [
            'status' => 200,
            'error'  => null,
            'messages' => [
                'success' => 'El registro ha sido guardado'
            ]
        ];
        return $this->respondCreated($response, 200);
    }

    /**
     * Return the editable properties of a resource object
     *
     * @return mixed
     */
    public function edit($id = null)
    {

    }

    /**
     * Add or update a model resource, from "posted" properties
     *
     * @return mixed
     */
    public function update($id = null)
    {
        $register = $this->model->find($id);
        if (!$register)
        {
            $response = [
                'status' => 404,
                'error'  => true,
                'messages' => [
                    'error' => 'Registro no encontrado'
                ]
            ];
            return $this->respondCreated($response, 404);
        }
        $request = $this->request->getJSON();
        $data = [
            'water_porc'    => $request->water_porc,
            'grain_porc'   => $request->amount_porc
        ];
        $this->model->update($id, $data);
        $response = [
            'status' => 200,
            'error'  => null,
            'messages' => [
                'success' => 'El registro ha sido actualizado'
            ]
        ];
        return $this->respondCreated($response, 200);

    }

    /**
     * Delete the designated resource object from the model
     *
     * @return mixed
     */
    public function delete($id = null)
    {
        $this->model->delete($id);
        $response = [
            'status' => 200,
            'error'  => null,
            'messages' => [
                'success' => 'El registro ha sido eliminado'
            ]
        ];
        return $this->respondCreated($response, 200);
    }
}
